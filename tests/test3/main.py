#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

import win32evtlog
import win32evtlogutil

class Logger(object):
    def __init__(self, appName):
        self.appName = appName

    def log_error(self, description):
        self._log_detail(description, win32evtlog.EVENTLOG_ERROR_TYPE)
    
    def log_information(self, description):
        self._log_detail(description, win32evtlog.EVENTLOG_INFORMATION_TYPE)

    def log_warning(self, description):
        self._log_detail(description, win32evtlog.EVENTLOG_WARNING_TYPE)

    def _log_detail(self, descripton, type):
        win32evtlogutil.ReportEvent(self.appName, 1, eventType=type, strings=[descripton])

def main():
    logger = Logger('Test3')
    
    logger.log_information('Test 3')

if __name__ == '__main__':
    main()