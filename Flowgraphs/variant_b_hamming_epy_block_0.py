import numpy as np
from gnuradio import gr


class hamming74_enc(gr.sync_block):
    def __init__(self):
        gr.sync_block.__init__(
            self,
            name="Hamming (7,4) Encoder",
            in_sig=[np.int8],
            out_sig=[np.int8]
        )

    def work(self, input_items, output_items):
        inp = input_items[0]
        out = output_items[0]

        n = len(inp) // 4
        out_len = min(len(out) // 7, n)

        for i in range(out_len):
            b = inp[i*4:(i+1)*4]

            out[i*7 + 0] = b[0]
            out[i*7 + 1] = b[1]
            out[i*7 + 2] = b[2]
            out[i*7 + 3] = b[3]

            out[i*7 + 4] = b[0] ^ b[1] ^ b[3]
            out[i*7 + 5] = b[0] ^ b[2] ^ b[3]
            out[i*7 + 6] = b[1] ^ b[2] ^ b[3]

        return out_len * 7
