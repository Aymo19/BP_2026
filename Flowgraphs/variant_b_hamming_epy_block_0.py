import numpy as np
from gnuradio import gr


class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block

    def __init__(self):  # only default arguments here
        gr.sync_block.__init__(
            self,
            name='(7,4) Hamming encoder',   # will show up in GRC
            in_sig=[np.int8]*4,
            out_sig=[np.int8]*7
        )

    def work(self, input_items, output_items):
        output_items[0][:] = input_items[0]
        output_items[1][:] = input_items[1]
        output_items[2][:] = input_items[2]
        output_items[3][:] = input_items[3]
        output_items[4][:] = input_items[0] ^ input_items[1] ^ input_items[3]
        output_items[5][:] = input_items[0] ^ input_items[2] ^ input_items[3]
        output_items[6][:] = input_items[1] ^ input_items[2] ^ input_items[3]
        return len(output_items[0])
