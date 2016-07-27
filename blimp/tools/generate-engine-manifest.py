#!/usr/bin/env python
# Copyright 2015 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

'''Generates a list of runtime Blimp Engine runtime dependencies.
'''


import argparse
import errno
import os
import subprocess
import sys
import tarfile

def main():
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('--build-dir',
                      help=('build output directory (e.g. out/Debug)'),
                      required=True,
                      metavar='DIR')
  parser.add_argument('--target',
                      help=('build target of engine'),
                      required=True)
  parser.add_argument('--output',
                      help=('name and path of manifest file to create'),
                      required=True,
                      metavar='FILE')
  args = parser.parse_args()

  try:
    deps = subprocess.check_output(['gn', 'desc', args.build_dir, args.target,
                                    'runtime_deps'])
  except subprocess.CalledProcessError as e:
    print "Error: " + ' '.join(e.cmd)
    print e.output
    exit(1)

  command_line = ' '.join([os.path.basename(sys.argv[0])] + sys.argv[1:])
  header = [
    '# Runtime dependencies for the Blimp Engine',
    '#',
    '# This file was generated by running:',
    '# ' + command_line + '',
    '#',
    '# Note: After generating, you should remove any unnecessary dependencies.',
    '',
  ]
  with open(args.output, 'w') as manifest:
    manifest.write('\n'.join(header))
    manifest.write(deps)

  print 'Created ' + args.output

if __name__ == "__main__":
  main()