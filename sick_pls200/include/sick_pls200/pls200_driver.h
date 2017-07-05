/*
Driver for the Sick PLS200 Laserscanner
Functionality:
OpenCommunication() will establish a serial connection with 500k Baud
StartContinuesStream() will set the Operation Mode of the Laser to... continues streaming
ReadLaserData() will give back 1 set of Range Data with 361 Points over 180° 
*/

#include <ros/ros.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>   
#include <string.h>  
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>   
#include <termios.h> 
#include <sys/time.h>
#include <sys/ioctl.h>

#include <sensor_msgs/LaserScan.h>
#include <angles/angles.h>

#define BUF_SIZE 1024
#define LOBYTE(w) ((uint8_t) (w & 0xFF))  //create lowbyte for comm
#define HIBYTE(w) ((uint8_t) ((w >> 8) & 0xFF))  //create highbyte for comm
#define MAKEUINT16(lo, hi) ((((uint16_t) (hi)) << 8) | ((uint16_t) (lo)))  //create int from 2 bytes


#define MAXNDATA 802
#define DEBUG



// Device codes

#define STX     0x02
#define ACK     0xA0
#define NACK    0x15
#define SICK_STATUS 0x31
#define CRC16_GEN_POL 0x8005
#define BAUD    38400   //9600 500000

const int CMD_BUFFER_SIZE = 255;

using namespace std;

  class SickPLS200
  {
    public:
      
		//Constructor
		SickPLS200 (string serialport);

		int 				laser_fd;  			//file descriptor for serial connection
		string 				serialport;			//serial port /dev/ttyUSB0
		vector<uint8_t> 	remaining_buffer;

		//Serial Port Functions
		int 	OpenSerial(int baudrate);
		void 	CloseSerial();
		int 	OpenCommunication();
		
		//Basic comm functions
		int	CreateCRC(vector<uint8_t> data);
		void CreateMsg(vector<uint8_t> data, vector<uint8_t> &msg);
		int	SendData(vector<uint8_t> msg);
		int ReadMsg(vector<uint8_t> &data);
		
		
		//Advanced comm functions
		int SendWithAswCheck(vector<uint8_t> data);
		int CheckSerial();
		int Reset();
		int Login();
		int LoginAndSetBaud();
		int Set9600Baud();
		int Set38kBaud();
		int Set500kBaud();
		int StartContinuesStream();
		int ReadLaserData(vector<uint16_t> &ranges);     

   };   
   
   //SickPLS200::SickPLS200(){};
   SickPLS200::SickPLS200(string serialport){
	   this->serialport = serialport;  
	   remaining_buffer.clear(); 
   }
   
   
   int SickPLS200::OpenSerial(int baudrate) {
	   
	    ROS_INFO("Open Serial Connection");
		this->laser_fd = ::open(this->serialport.c_str(), O_RDWR | O_SYNC , S_IRUSR | S_IWUSR );
//		this->laser_fd = ::open(this->serialport.c_str(), O_RDWR | O_SYNC , S_IRUSR | S_IWUSR | O_NONBLOCK );

		if (this->laser_fd < 0)
		{
			ROS_ERROR("unable to open serial port [%s]; [%s]", this->serialport.c_str(), strerror(errno));
			return 1;
		}

		struct termios term;
		if( tcgetattr( this->laser_fd, &term ) < 0 ){
			ROS_ERROR("Unable to get serial port attributes");
			return 1;
		}

		cfmakeraw( &term );
		
		term.c_cflag |= (CLOCAL | CREAD);
		term.c_cflag |= PARENB;
		term.c_cflag &= ~PARODD;
		term.c_cflag &= ~CSTOPB;
		term.c_cflag &= ~CSIZE;
		term.c_cflag |= CS8;
		term.c_cc[VMIN]  = 0;
		term.c_cc[VTIME]  = 10;
		
		//check for correct baudrate:
		cfsetispeed( &term, baudrate );
		cfsetospeed( &term, baudrate);
		if( tcsetattr( this->laser_fd, TCSAFLUSH, &term ) < 0 ){
			ROS_INFO("Unable to set serial port attributes");
			return 1;
		}
		// Make sure queue is empty
		tcflush(this->laser_fd, TCIOFLUSH);
		if (CheckSerial() == 0){
			return 0;
		}
		ROS_ERROR("Can't communicate with LASER");		
		return 1;
	}   
   
	void SickPLS200::CloseSerial(){

		ROS_INFO("Closing Serial Connection");
		Login();
		close(this->laser_fd);
	}
	
	int SickPLS200::OpenCommunication(){
		//try our 3 baudrates and set speed to 500k
		//ROS_INFO("Testing 500k Baud");
		//if(OpenSerial(B500000) == 0){			
		//	return LoginAndSetBaud();
		//}
		ROS_INFO("Testing 38.4k Baud");
		if(OpenSerial(B38400) == 0){
			return LoginAndSetBaud();
		}
		ROS_INFO("Testing 9600 Baud");
		if(OpenSerial(B9600) == 0){
			return LoginAndSetBaud();
		}			
			return 1;
	}	
	
	int SickPLS200::LoginAndSetBaud(){
		Login();
		return Set38kBaud();		
	}
	
	int SickPLS200::CreateCRC(vector<uint8_t> data)
	{
		uint16_t uCrc16;
		uint8_t abData[2];

		uCrc16 = 0;
		abData[0] = 0;

		while(data.size()){
			abData[1] = abData[0];
			abData[0] = data.front();
			data.erase(data.begin());

			if( uCrc16 & 0x8000 ){
				uCrc16 = (uCrc16 & 0x7fff) << 1;
				uCrc16 ^= CRC16_GEN_POL;
			}
			else {
				uCrc16 <<= 1;
			}
				uCrc16 ^= MAKEUINT16(abData[0],abData[1]);
		}
		#ifdef DEBUG
			stringstream ss;
			ss << setw(2) << setfill('0') << hex << (int) LOBYTE(uCrc16) << " " << setw(2) << setfill('0') << hex << (int) HIBYTE(uCrc16);
			//ROS_INFO("CRC test %s", ss.str().c_str());
		#endif
		
		return (uCrc16);
	}
	
	void SickPLS200::CreateMsg(vector<uint8_t> data, vector<uint8_t> &msg){
		
		msg.clear();

		// Create header
		msg.push_back(STX);
		msg.push_back(0x00);
		msg.push_back(LOBYTE((uint16_t)data.size()));
		msg.push_back(HIBYTE((uint16_t)data.size()));
		
		msg.insert(msg.end(), data.begin(), data.end()); //add data to msg

		// Create and add CRC
		uint16_t crc = CreateCRC(msg);
		msg.push_back(LOBYTE(crc));
		msg.push_back(HIBYTE(crc));
			
	}
	
	
	int SickPLS200::SendData(vector<uint8_t> data){
		
		vector<uint8_t> msg;
		
		CreateMsg(data, msg);	

		// Make sure both input and output queues are empty
		tcflush(this->laser_fd, TCIOFLUSH);

		int bytes = 0;
		char* msg_buffer = new char[msg.size()](); //create the char array for sending
		for(int i = 0; i < msg.size(); i++){
			msg_buffer[i] = msg[i];
		}

		bytes = ::write( this->laser_fd, msg_buffer ,(ssize_t) msg.size());	

		// Make sure the queue is drained
		::tcdrain(this->laser_fd);
		
		#ifdef DEBUG
			stringstream ss;
			for(int i = 0; i < msg.size(); i++){
				ss << setw(2) << setfill('0') << hex << (int) msg_buffer[i] << " ";
			}
			ROS_INFO("Sent: %s", ss.str().c_str());
		#endif

		// Return the actual number of bytes sent, including header and footer
		return bytes;	
	}
	
	//Read a message from the serial port and do a CRC check
	int SickPLS200::ReadMsg(vector<uint8_t> &msg){
		
		
		int bytes_avail;
		int timeout = 0;
		while(1){
			::ioctl(this->laser_fd, FIONREAD, &bytes_avail);
			if (bytes_avail == 0){			
				ros::Rate(10).sleep();
				timeout++;
				if (timeout > 20){
					ROS_ERROR("No bytes available on serial port1");
					return 1;
				}
			} else {
				break;
			}
		}
		
		
		uint8_t buffer[1024];

		int bytes = remaining_buffer.size();
		for (int i = 0; i < bytes; i++){
			buffer[i] = remaining_buffer[i];
		}
		
		remaining_buffer.clear();
		while(1){
			::ioctl(this->laser_fd, FIONREAD, &bytes_avail);
			if (bytes_avail == 0){			
				ros::Rate(10).sleep();
				timeout++;
				if (timeout > 20){
					ROS_ERROR("No bytes available on serial port2");
					return 1;
				}
			} else {
				break;
			}
		}
		
		
		int new_bytes = ::read(this->laser_fd, buffer+bytes, sizeof(buffer)-bytes);
		if (new_bytes < 0)
		{
		  if (errno == EINTR)
		  ROS_ERROR("error on read (1)");
		  return 1;
		}
		if (!new_bytes)
		{
		  ROS_ERROR("eof on read (1)");
		  return 1;
		}
		
		bytes += new_bytes;
		
		int cnt = 0;
		timeout = 0;		
		while (bytes < 6) {  //when we have less bytes then header + checksum read again
			ROS_INFO("3. bytes less then header + checksum");
			while(1){
				::ioctl(this->laser_fd, FIONREAD, &bytes_avail);
				if (bytes_avail == 0){			
					ros::Rate(10).sleep();
					timeout++;
					if (timeout > 20){
						ROS_ERROR("No bytes available on serial port3");
						return 1;
					}
				} else {
					break;
				}
			}
			bytes = bytes + ::read(this->laser_fd, buffer+bytes, sizeof(buffer)-bytes);
			cnt++;
			if(cnt == 5){
				return 1;
			}
			timeout=0;
		}
	
		//now we have to find the header 0x02 0x80 len_lo len_hi cmd
		int i = 0;
		int length = 0;		
		while (i < bytes-1) { //search of 0x02 0x80 in the front of the message 
			if (buffer[i] == 0x02 && buffer[i+1] == 0x80){
				length = MAKEUINT16(buffer[i+2], buffer[i+3]); //check if length is valid
				if(length != 3){ //short ACK message
					if(length != 726){  //data message
            i++;
						continue;
					}
				}
				break;
			}
			i++;			
		}
		
		
		if (buffer[i] != 0x02 || buffer[i+1] != 0x80 || i == bytes-1){
			return 1;
		}
				
		//now shift everything to the beginning of the buffer		
		copy(buffer+i, buffer+i+bytes, buffer);
		bytes = bytes - i;
		
		int diff = length + 4 + 2 - bytes;   //length + header + crc - what we have
		if(diff + bytes > 1024){
			ROS_ERROR("Message length to long");
			return 1;
		}
		timeout = 0;
		while (diff > 0){ //we only read part of the message, lets add the rest
			while(1){
				::ioctl(this->laser_fd, FIONREAD, &bytes_avail);
				if (bytes_avail < diff){			
					ros::Rate(100).sleep();
					timeout++;
					if (timeout > 20){
						ROS_ERROR("No bytes available on serial port4");
						return 1;
					}
				} else {
					break;
				}
			}			
			bytes = bytes + ::read(this->laser_fd, buffer+bytes, diff);
			diff = length + 4 + 2 - bytes;
			timeout=0;
		}
		
		if(bytes > 732){ //strange stuff
			//ROS_INFO("message completely read %d, length = %d", bytes, length);
		}
		
		//now check the CRC
		uint16_t crc = MAKEUINT16(buffer[3+length+1], buffer[3+length+2]);
		
		
		for(int k = 0; k < 4+length; k++){
			msg.push_back(buffer[k]);
		}
		
		remaining_buffer.clear();
		for(int k = 4+length; k < bytes; k++){
			remaining_buffer.push_back(buffer[k]);
		}
		
		uint16_t crc_from_msg = CreateCRC(msg);
		
		
		if(crc == crc_from_msg){
			return 0;
		} else {
			ROS_ERROR("Checksum wrong");
			return 1;
		}
		
		
	}	
	
	int SickPLS200::SendWithAswCheck(vector<uint8_t> data){		
		
		int cnt = 0;
		while(cnt < 5){	
			SendData(data); // send the message		
			ros::Duration(0.5).sleep();
			vector<uint8_t> asw;
			if(ReadMsg(asw) == 0){				
				if(asw[4] == ACK){
					ROS_INFO("ACK received");
					return 0;
				}				
			}
			cnt++;			
		}		
		return 1;
	}
	 
	//stop the continues stream and check for ACK
	int SickPLS200::CheckSerial(){
		
		vector<uint8_t> data;		
		
		data.clear();			
		data.push_back(0x20);
		data.push_back(0x25);
		
		return SendWithAswCheck(data);
	}	
	
	//Login with password
	int SickPLS200::Login(){
		
		vector<uint8_t> data;		
		
		string pw = "SICK_PLS";
		
		data.clear();		
		data.push_back(0x20);
		data.push_back(0x00);
		for(int i = 0; i < pw.size(); i++){
			data.push_back((uint8_t) pw[i]);
		}		
		
		if(SendWithAswCheck(data) == 0){			
			ROS_INFO("Logged in");			
			return 0;		
		}
		return 1;
	}
	
	int SickPLS200::Reset(){
		vector<uint8_t> data;	
		
		data.clear();		
		data.push_back(0x10);	
		if(SendData(data) == 0){
			return 0;		
		}			
		return 1;
	}
	
	int SickPLS200::Set9600Baud(){
		ROS_INFO("Set 9600 Baud");
		
		Login();
		
		vector<uint8_t> data;	
		
		data.clear();		
		data.push_back(0x20);
		data.push_back(0x42);			
		
		if(SendWithAswCheck(data) == 0){				
			CloseSerial();
			if(OpenSerial(B9600) == 0){
				ROS_INFO("9600 Baud Set");			
				return 0;
			}	
		}
		return 1;
	}

	int SickPLS200::Set38kBaud(){
		ROS_INFO("Set 38k Baud");
		
		Login();
		
		vector<uint8_t> data;	
		
		data.clear();		
		data.push_back(0x20);
		data.push_back(0x40);			
		
		if(SendWithAswCheck(data) == 0){				
			CloseSerial();
			if(OpenSerial(B38400) == 0){
				ROS_INFO("38k Baud Set");			
				return 0;
			}		
		}
		return 1;
	}	
	
	int SickPLS200::Set500kBaud(){
		ROS_INFO("Set 500k Baud");
		
		Login();
		
		vector<uint8_t> data;	
		
		data.clear();		
		data.push_back(0x20);
		data.push_back(0x48);			
		
		if(SendWithAswCheck(data) == 0){				
			CloseSerial();
			if(OpenSerial(B500000) == 0){
				ROS_INFO("500k Baud Set");			
				return 0;
			}		
		}
		return 1;
	}	
	
	//start the continues stream and check for ACK
	int SickPLS200::StartContinuesStream(){
		ROS_INFO("StartContinuesStream");
		vector<uint8_t> data;	
		
		data.clear();		
		data.push_back(0x20);
		data.push_back(0x24);
			
		
		if(SendWithAswCheck(data) == 0){			
			ROS_INFO("Started continues Stream");			
			return 0;		
		}
		return 1;
	}
	
	//reads data from the serial port controls crc and status byte	
	int SickPLS200::ReadLaserData(vector<uint16_t> &ranges){
		ranges.clear();
		vector<uint8_t> msg;
		if (ReadMsg(msg) == 0){				
			//create the range data from the msg starting at [7]+[8] for 361 data points
			for (int i = 7; i < 7+722; i+=2){
				ranges.push_back(msg[i] | (msg[i+1] << 8));				
			}
			return 0;	
		}		
		return 1;
	}
	
	
	
   

