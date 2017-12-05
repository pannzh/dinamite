#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import json
import argparse
def rotate_map(themap):
    _newmap = {}
    for k in themap:
        assert themap[k] not in _newmap
        _newmap[themap[k]] = k
    _newmap[-1] = 'n/a'
    return _newmap

def load_map(map_file):
    with open(map_file, 'r') as f:
        origin_map = json.load(f)
    return rotate_map(origin_map)

def print_value_range(filename, mapsdir):
    map_variables = load_map(os.path.join(mapsdir, 'map_variables.json'))
    map_types = load_map(os.path.join(mapsdir, 'map_types.json'))
    map_sources = load_map(os.path.join(mapsdir, 'map_sources.json'))
    ret = {}
    with open(filename, 'r') as f:
        for trace in f:
            try:
                _, value, accessType, fileId, line, _,\
                typeId, varId, tainted = trace.split()
                varId = int(varId)
                typeId = int(typeId)
                fileId = int(fileId)
                if 'float' in map_types[typeId]:
                    value = float(value)
                else:
                    value = int(value)
            except ValueError:
                continue
            varName = u'{}:{} {}'.format(map_sources[fileId], line, map_variables[varId])
            if varName not in ret:
                ret[varName] = {}
            if 'min' not in ret[varName]:
                ret[varName]['min'] = value
            if 'max' not in ret[varName]:
                ret[varName]['max'] = value
            if accessType not in ret[varName]:
                # access type (r/w/a)
                ret[varName][accessType] = 0
            ret[varName]['min'] = ret[varName]['min'] if value > ret[varName]['min'] else value
            ret[varName]['max'] = ret[varName]['max'] if value < ret[varName]['max'] else value
            ret[varName][accessType] += 1
    print(json.dumps(ret, indent=4))

def print_hot_area(filename, mapsdir):
    map_variables = load_map(os.path.join(mapsdir, 'map_variables.json'))
    map_types = load_map(os.path.join(mapsdir, 'map_types.json'))
    map_sources = load_map(os.path.join(mapsdir, 'map_sources.json'))
    map_blocks = load_map(os.path.join(mapsdir, 'map_blocks.json'))
    ret = {}
    with open(filename, 'r') as f:
        for trace in f:
            try:
                blockId, fileId, lineNum = trace.split()
                blockId = int(blockId)
                fileId = int(fileId)
            except ValueError:
                continue
            blockName = u'{}:{} {}'.format(map_sources[fileId], lineNum, map_blocks[blockId])
            if blockName not in ret:
                ret[blockName] = 0
            ret[blockName] += 1
    print(json.dumps(ret, indent=4))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='value range analyser')
    parser.add_argument('-m', '--maps', required=True, help='directory of map files')
    parser.add_argument('-a', '--analysis', required=True, choices=['value', 'block'], help='analysis type')
    parser.add_argument('-t', '--trace', required=True, help='location of the trace file')

    args = parser.parse_args()
    if args.analysis == 'value':
        print_value_range(args.trace, args.maps)
    elif args.analysis == 'block':
        print_hot_area(args.trace, args.maps)

