#     Copyright 2014-2015 Emiliano Mennucci
#
#     This file is part of VLAM.
# 
#     VLAM is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
# 
#     VLAM is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
# 
#     You should have received a copy of the GNU General Public License
#     along with VLAM.  If not, see <http://www.gnu.org/licenses/>.

import os

env = Environment()

env.Append(CPPPATH = ['#src'])
env.Append(CPPFLAGS = ['-Wall', '-Werror', '-g', '-std=c++11'])

libvlam = SConscript(os.path.join('src', 'SConscript'), exports = 'env')
SConscript(os.path.join('test', 'SConscript'), exports = 'env libvlam')

# Alias for copying include and lib files
dest_dir = [os.path.join("install", "libvlam.a"), os.path.join("install", "vlam", "vlam.h")]
src_dir = [libvlam, os.path.join("src", "vlam", "vlam.h")]
env.Alias('lib', env.InstallAs(["install/libvlam.a", "install/vlam/vlam.h"], [libvlam, "src/vlam/vlam.h"]))

Default('vlam_parse')
