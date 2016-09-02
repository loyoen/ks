''' 
 
/**
 * @file client.py
 * @author luoyongen(com@baidu.com)
 * @date 2016/07/31 12:17:51
 * @brief 
 *  
 **/
 '''
import httplib
httpClient = None
while True:
    try:
        httpClient = httplib.HTTPConnection('localhost',8000,timeout=30)
        httpClient.request('get','/')
        response = httpClient.getresponse()
        print response.status
        print response.reason
        print response.read()
        if response.status != 200:
            break
        httpClient.close()
    except:
        print "e"
        break
#if httpClient:
#    httpClient.close()





















'''
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
'''
