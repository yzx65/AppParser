
def print_table(title, headers, rows):
    widths = []
    
    for i in xrange(len(headers)):
        z = map(len, [readUtf8Text(row[i]) for row in rows])
        z.append(len(headers[i]))
        widths.append(max(z))
    
    width = sum(widths) + len(headers) + 1
    print "-"* width
    print "|" + title.center(width-2) + "|"
    print "-"* width
    hline = "|"
    for i in xrange(len(headers)):
        hline += headers[i].ljust(widths[i]) + "|"
    print hline

    print "-"* width
    for row in rows:
        line = "|"
        for i in xrange(len(row)):
            line += readUtf8Text(row[i]).ljust(widths[i]) + "|"
        print line
    
    if len(rows) == 0:
        print "|" + "No entries".center(width-2) + "|"
    print "-"* width
    print ""
    
def readUtf8Text(text):
    try:
        if isinstance(text, unicode):
            data = text
        else:
            data = unicode(text, 'utf8')
        #data = data.encode('GB18030')
        return data
    except:
        pass

    try:
        data = unicode(text, 'GB18030')
        #data = data.encode('GB18030')
        return data
    except:
        #print "WARNING: UnicodeDecodeError : %s" % ":".join("{:02x}".format(ord(c)) for c in text)
        data = dumpHexText(text)
        pass
    return data

def dumpHexText(text):
    data = ''
    for c in text:
        if (ord(c) >= 127 and ord(c) <= 255) or (ord(c) <= 20):
            data += ":" + "{:02x}".format(ord(c)) + ":" 
        else:
            data += c
    return data

    
