#!/usr/bin/python3

# make session
def makeSessionId(st):
    import md5, time, base64, string
    m = md5.new()
    m.update('this is a test of the emergency broadcasting system')
    m.update(str(time.time()))
    m.update(str(st))
    return string.replace(base64.encodestring(m.digest())[:-3],'/','/')

def makeSessionId_nostring(st):
    import md5, time, base64
    m = md5.new()
    m.update('this is a test of the emergency broadcasting system')
    m.update(str(time.time()))
    m.update(str(st))
    return base64.encodestring(m.digest())[:-3].replace('/','/')

test1 = makeSessionId('abc')
print(test1)
