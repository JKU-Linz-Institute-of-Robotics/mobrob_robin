from __future__ import division
import math
import os
import random
import time
import roslib

from python_qt_binding import loadUi
from python_qt_binding.QtCore import Qt, Slot, qWarning, QTimer, QEvent
from python_qt_binding.QtGui import QIcon, QMenu, QTreeWidgetItem, QWidget, QLabel, QCheckBox

import rospkg
import rospy
import genpy
import rosservice

from rqt_py_common.extended_combo_box import ExtendedComboBox
from urdf_parser_py.urdf import URDF
from std_msgs.msg import Float64MultiArray
from geometry_msgs.msg import Twist


class MobrobDashboardWidget(QWidget):
    column_names = ['service', 'type', 'expression']
    
    def __init__(self):
        super(MobrobDashboardWidget, self).__init__()
        self.setObjectName('MobrobDashboardWidget')
        
        # create context for the expression eval statement
        self._eval_locals = {}
        for module in (math, random, time):
            self._eval_locals.update(module.__dict__)
        self._eval_locals['genpy'] = genpy
        del self._eval_locals['__name__']
        del self._eval_locals['__doc__']

        rp = rospkg.RosPack()
        ui_file = os.path.join(rp.get_path('mobrob_robin_rqt'), 'resource', 'MobrobDashboard.ui')
        loadUi(ui_file, self, {'ExtendedComboBox': ExtendedComboBox})

        self._column_index = {}
        for column_name in self.column_names:
            self._column_index[column_name] = len(self._column_index)
        
        
               
        self._twist = Twist() 
        self.base_activated = False
        self._pub =  rospy.Publisher('/mobrob_robin/base/drives/control/cmd_vel', Twist, queue_size = 1) 
        
        
        self._timer_refresh_state = QTimer(self)
        self._timer_refresh_state.timeout.connect(self._timer_update)
        self.start()
        
        
    def start(self):
        self._timer_refresh_state.start(10)                  

    #def save_settings(self, plugin_settings, instance_settings):

    def shutdown_plugin(self):
        self._timer_refresh_state.stop()
        self._sub_lwa_state.unregister()
        self._sub_gripper_state.unregister()
        self._sub_pan_tilt_state.unregister()

    #def restore_settings(self, plugin_settings, instance_settings):

    #def trigger_configuration(self):
    
    def _timer_update(self):
        self._publish_twist()
        self._update_goals()


    def _publish_twist(self):
               
        if self.base_activated:
            self._pub.publish(self._twist)   
       

    @Slot()
    def refresh_state(self):
        self.test_label.setText('test')   
        
    def call_service( self, string ):
        service_name = string
        service_class = rosservice.get_service_class_by_name( service_name )
        service = rospy.ServiceProxy(service_name, service_class)
        request = service_class._request_class()
        try:
            response = service()
        except rospy.ServiceException as e:
            qWarning('service_caller: request:\n%r' % (request))
            qWarning('service_caller: error calling service "%s":\n%s' % (self._service_info['service_name'], e))           
        #else:
            #print(response)            
    
            
##### Base
    def _base_move(self, x, y, yaw):
        twist = Twist()
        twist.linear.x = x;
        twist.linear.y = y;
        twist.angular.x = 0.0;
        twist.angular.y = 0.0;
        twist.angular.z = yaw; 
        self._twist =  twist

    def _base_stop_motion(self):
	self.base_activated = False
        self._base_move(0.0, 0.0, 0.0)
	self._pub.publish(self._twist)
	
        
    @Slot()
    def on_base_start_clicked(self):
        self.call_service( '/mobrob_robin/base/drives/control/reference' )    
    
    def on_base_start_clicked(self):
        self.call_service( '/mobrob_robin/base/drives/control/start' )
     
    @Slot()    
    def on_base_stop_clicked(self):
        self.call_service( '/mobrob_robin/base/drives/control/stop' )
            
    @Slot()
    def on_base_forward_pressed(self):
        self._base_move(0.3, 0.0, 0.0)
	self.base_activated = True
 
    @Slot()
    def on_base_forward_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_back_pressed(self):
        self._base_move(-0.3, 0.0, 0.0)
	self.base_activated = True
 
    @Slot()
    def on_base_back_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_left_pressed(self):
        self._base_move(0.0, 0.3, 0.0)
	self.base_activated = True
 
    @Slot()
    def on_base_left_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_right_pressed(self):
        self._base_move(0.0, -0.3, 0.0)
	self.base_activated = True
 
    @Slot()
    def on_base_right_released(self):
        self._base_stop_motion()

    @Slot()
    def on_base_turn_left_pressed(self):
        self._base_move(0.0, 0.0, 0.5)
	self.base_activated = True
 
    @Slot()
    def on_base_turn_left_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_turn_right_pressed(self):
        self._base_move(0.0, 0.0, -0.5)
	self.base_activated = True
 
    @Slot()
    def on_base_turn_right_released(self):
        self._base_stop_motion()
        
    #diagonal
    @Slot()
    def on_base_forward_left_pressed(self):
        self._base_move(0.2, 0.2, 0.0)
	self.base_activated = True
     
    @Slot()
    def on_base_forward_left_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_forward_right_pressed(self):
        self._base_move(0.2, -0.2, 0.0)
	self.base_activated = True
     
    @Slot()
    def on_base_forward_right_released(self):
        self._base_stop_motion()
        
     
    @Slot()   
    def on_base_back_left_pressed(self):
        self._base_move(-0.2, 0.2, 0.0)
	self.base_activated = True
     
    @Slot()
    def on_base_back_left_released(self):
        self._base_stop_motion()
        
    @Slot()
    def on_base_back_right_pressed(self):
        self._base_move(-0.2, -0.2, 0.0)
	self.base_activated = True
     
    @Slot()
    def on_base_back_right_released(self):
        self._base_stop_motion()
    
