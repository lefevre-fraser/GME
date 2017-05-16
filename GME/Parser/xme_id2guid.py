import os
import os.path
import sys

def id2guid(input, output, sort_elements=False, omit_default_attributes=False):
    from xml.etree import ElementTree
    xme = ElementTree.parse(input)
    id_guid_map = {}
    for element in xme.iter():
        if element.get('id') and element.get('guid'):
            id_guid_map[element.get('id')] = element.get('guid')
            del element.attrib['id']
    for element in xme.iter():
        if element.get('derivedfrom'):
            element.attrib['derivedfrom'] = id_guid_map[element.get('derivedfrom')]
    for element in xme.iter('reference'):
        if element.get('referred'):
            element.attrib['referred'] = id_guid_map[element.get('referred')]
    for element in xme.iter('set'):
        if element.get('members'):
            element.attrib['members'] = " ".join(sorted([id_guid_map[id] for id in element.get('members').split()]))
    for element in xme.iter('connpoint'):
        if element.get('target'):
            element.attrib['target'] = id_guid_map[element.get('target')]
        if element.get('refs'):
            element.attrib['refs'] = " ".join([id_guid_map[id] for id in element.get('refs').split()])

    if omit_default_attributes:
        parent_map = dict((c, p) for p in xme.getiterator() for c in p)
        for element in xme.findall('.//attribute[@status=\'meta\']'):
            parent_map[element].remove(element)

    if sort_elements:
        def sortchildrenby(parent, attr):
            parent[:] = sorted(parent, key=lambda child: child.get(attr))

        for element in list(xme.iter()):
            sortchildrenby(element, 'name')
            sortchildrenby(element, 'guid')

    output.write('<!DOCTYPE project SYSTEM "mga2.dtd">\n')
    xme.write(output)

if __name__ == '__main__':
    import argparse

    parser = argparse.ArgumentParser(description='Convert GME id-style .xme (mga.dtd) to GUID-style .xme (mga2.dtd).')
    parser.add_argument('--sort', action='store_true')
    parser.add_argument('--omit-default-attributes', action='store_true')
    parser.add_argument('input-xme-file')
    # parser.add_argument('--output-file')

    args = parser.parse_args()
    input = vars(args)['input-xme-file']
    options = {
        "sort_elements": args.sort,
        "omit_default_attributes": 'omit-default-attributes' in vars(args)
    }
    if input != '-':
        output_filename = os.path.splitext(input)[0] + "_guids.xme"
        with open(output_filename, 'wb') as output:
            id2guid(input, output, **options)
    else:
        id2guid(sys.stdin, sys.stdout, **options)

