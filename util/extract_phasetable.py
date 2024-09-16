# JUMMY WAS HERE
# extract phase table from speedy blupi 2.2 english ver

import sys
import io

offset = 0x3d400

outs = []

with io.open('BLUPI.exe', 'rb') as f:
	data = f.read()
	outs.append('static Phase table[] =')
	outs.append('{')
	for i in range(39):
		
		poff = offset + i * 7084
		p = int.from_bytes(data[poff : poff + 4], 'little')
		if p == 0:
			outs.append('{0}')
			break
		outs.append('{')
		outs.append(str(p) + ',')
		outs.append('"' + data[poff + 4 : poff + 36].decode('ascii').rstrip('\x00') + '",')
		outs.append('TRUE,' if int.from_bytes(data[poff + 36 : poff + 40], 'little') != 0 else 'FALSE,')
		outs.append('TRUE,' if int.from_bytes(data[poff + 40 : poff + 44], 'little') != 0 else 'FALSE,')
		outs.append('{')
		for j in range(40):
			boff = poff + 44 + j * 176
			b = int.from_bytes(data[boff : boff + 4], 'little')
			if b == 0:
				outs.append('{0}')
				break
			else:
				outs.append('{')
				outs.append(str(b) + ',')
				s = ''
				s += str(int.from_bytes(data[boff + 4 : boff + 8], 'little')) + ', '
				m = int.from_bytes(data[boff + 8 : boff + 12], 'little')
				if m == 0:
					s += '{0},'
				else:
					s += '{' + str(m) + ', '
					for k in range(m):
						moff = boff + 12 + k * 4
						s += str(int.from_bytes(data[moff : moff + 4], 'little')) + ', '
					s += '},'
				outs.append(str(s))
				outs.append(str(int.from_bytes(data[boff + 88 : boff + 92], 'little')) + ', ' + str(int.from_bytes(data[boff + 92 : boff + 96], 'little')) + ',')
				s = ''
				t = int.from_bytes(data[boff + 96 : boff + 100], 'little')
				if t == 0:
					s += '{0}'
				else:
					s += '{ ' + str(t) + ', '
					for k in range(t):
						toff = boff + 100 + k * 4
						s += str(int.from_bytes(data[toff : toff + 4], 'little')) + ', '
					s += '}'
				outs.append(str(s))
			outs.append('},')
		outs.append('},')
		outs.append('},')
	outs.append('},')
outs.append('};')
				 
with io.open('out.h', 'wb') as f2:
	f2.write(bytearray('\n'.join(outs), 'ascii'))
