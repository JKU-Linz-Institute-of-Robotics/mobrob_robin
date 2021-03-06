from rqt_gui_py.plugin import Plugin
from .mobrob_dashboard_widget import MobrobDashboardWidget

class MobrobDashboard(Plugin):

    def __init__(self, context):
        super(MobrobDashboard, self).__init__(context)
        self.setObjectName('MobrobDashboard')

        self._widget = MobrobDashboardWidget()
        if context.serial_number() > 1:
            self._widget.setWindowTitle(self._widget.windowTitle() + (' (%d)' % context.serial_number()))
        context.add_widget(self._widget)

    #def save_settings(self, plugin_settings, instance_settings):
    #    self._widget.save_settings(plugin_settings, instance_settings)

    #def restore_settings(self, plugin_settings, instance_settings):
    #    self._widget.restore_settings(plugin_settings, instance_settings)

    #def trigger_configuration(self):
    #    self._widget.trigger_configuration()
