import numpy as np
from gnuradio import gr

class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block

    def __init__(self):  # only default arguments here
        gr.sync_block.__init__(
            self,
            name='(7,4) Hamming decoder',   # will show up in GRC
            in_sig=[np.int8]*7,
            out_sig=[np.int8]*4
        )

    def work(self, input_items, output_items):
        syndromes_map = {
            1: 4,  # p0
            2: 5,  # p1
            3: 0,  # c0
            4: 6,  # p2
            5: 1,  # c1
            6: 2,  # c2
            7: 3   # c3
        }
        syndrome_1 = input_items[0] ^ input_items[1] ^ input_items[3] ^ input_items[4]
        syndrome_2 = input_items[0] ^ input_items[2] ^ input_items[3] ^ input_items[5]
        syndrome_3 = input_items[1] ^ input_items[2] ^ input_items[3] ^ input_items[6]
        syndromes = syndrome_1 + syndrome_2 * 2 + syndrome_3 * 4
        for i, syndrome in enumerate(syndromes):
        	#if syndrome != 0:
        		#input_items[syndromes_map[syndrome]][i] = 1 - input_items[syndromes_map[syndrome]][i]
        	if syndrome == 3:
        		input_items[0][i] = 1 - input_items[0][i]
        	elif syndrome == 5:
        		input_items[1][i] = 1 - input_items[1][i]
        	elif syndrome == 6:
        		input_items[2][i] = 1 - input_items[2][i]
        	elif syndrome == 7:
        		input_items[3][i] = 1 - input_items[3][i]
        	elif syndrome == 1:
        		input_items[4][i] = 1 - input_items[4][i]
        	elif syndrome == 2:
        		input_items[5][i] = 1 - input_items[5][i]
        	elif syndrome == 4:
        		input_items[6][i] = 1 - input_items[6][i]
        output_items[0][:] = input_items[0]
        output_items[1][:] = input_items[1]
        output_items[2][:] = input_items[2]
        output_items[3][:] = input_items[3]
        return len(output_items[0])
