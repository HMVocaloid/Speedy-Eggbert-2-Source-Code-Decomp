# JUMMY WAS HERE
# extract pixtables from speedy blupi 2.2 english ver

import sys
import io

offsets = {}
offsets['table_icon_blupi'] = 0x81bf8
offsets['table_icon_element'] = 0x84070
offsets['table_icon_explo'] = 0x84e00
offsets['table_icon_object'] = 0x82bc0

outs = {}

with io.open('BLUPI.exe', 'rb') as f:
	data = f.read()
	for k, v in offsets.items():
		lg = int.from_bytes(data[v : v + 2], 'little')
		outs[k] = []
		outs[k].append("extern short " + k + "[]{");
		outs[k].append(str(lg) + ',');
		for i in range(lg):
			string = ''
			for j in range(6):
				string += str(int.from_bytes(data[v + i*12 + j*2 + 2 : v + i*12 + j*2 + 4], 'little')) + ','
				if j % 2 == 1:
					string += ' '
			outs[k].append(string)
		outs[k].append('};')
with io.open('out.h', 'wb') as f2:
	f2.write(bytearray(('\n\n'.join(['\n'.join(w) for w in [v for _, v in outs.items()]])), 'ascii'))
