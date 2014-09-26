import os
import os.path
import sys

def id2guid(filename, output_filename):
    from xml.etree import ElementTree
    xme = ElementTree.parse(filename)
    id_guid_map = {}
    for element in xme.iter():
        if element.get('id') and element.get('guid'):
            id_guid_map[element.get('id')] = element.get('guid')
            del element.attrib['id']
        if element.get('derivedfrom'):
            element.attrib['derivedfrom'] = id_guid_map[element.get('derivedfrom')]
    for element in xme.iter('reference'):
        if element.get('referred'):
            element.attrib['referred'] = id_guid_map[element.get('referred')]
    for element in xme.iter('set'):
        if element.get('members'):
            element.attrib['members'] = " ".join([id_guid_map[id] for id in element.get('members').split()])
    for element in xme.iter('connpoint'):
        if element.get('target'):
            element.attrib['target'] = id_guid_map[element.get('target')]
        if element.get('refs'):
            element.attrib['refs'] = " ".join([id_guid_map[id] for id in element.get('refs').split()])
    
    with open(output_filename, 'wb') as output:
        output.write('<!DOCTYPE project SYSTEM "mga2.dtd">\n')
        xme.write(output)

if __name__ == '__main__':
    input = sys.argv[1]
    output = os.path.splitext(input)[0] + "_guids.xme"
    id2guid(input, output)
