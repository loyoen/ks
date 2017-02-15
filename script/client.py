''' 
 
/**
 * @file client.py
 * @author loyoen(com@gmail.com)
 * @date 2016/07/31 12:17:51
 * @brief 
 *  
 **/
 '''
import httplib
httpClient = None
httpClient = httplib.HTTPConnection('localhost',8000,timeout=30)
while True:
    try:
        httpClient.request('get','/')
        response = httpClient.getresponse()
        #print response.status
        #print response.reason
        response.read()
        if response.status != 200:
            break
    except:
        print "e"
        break
#if httpClient:
#    httpClient.close()





















'''
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
'''
