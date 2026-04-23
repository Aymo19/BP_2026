import numpy as np
from gnuradio import gr


class hamming74_dec(gr.sync_block):
    def __init__(self):
        gr.sync_block.__init__(
            self,
            name="Hamming (7,4) Decoder",
            in_sig=[np.int8],
            out_sig=[np.int8]
        )

    def work(self, input_items, output_items):
        inp = input_items[0]
        out = output_items[0]

        n = len(inp) // 7
        out_len = min(len(out) // 4, n)

        for i in range(out_len):
            c = inp[i*7:(i+1)*7]

            # syndrome
            s1 = c[0] ^ c[1] ^ c[3] ^ c[4]
            s2 = c[0] ^ c[2] ^ c[3] ^ c[5]
            s3 = c[1] ^ c[2] ^ c[3] ^ c[6]
            syndrome = s1 + (s2 << 1) + (s3 << 2)

            # correct copy (do NOT modify input)
            c = list(c)

            if syndrome == 3:
                c[0] ^= 1
            elif syndrome == 5:
                c[1] ^= 1
            elif syndrome == 6:
                c[2] ^= 1
            elif syndrome == 7:
                c[3] ^= 1
            elif syndrome == 1:
                c[4] ^= 1
            elif syndrome == 2:
                c[5] ^= 1
            elif syndrome == 4:
                c[6] ^= 1

            # output original 4 bits
            out[i*4 + 0] = c[0]
            out[i*4 + 1] = c[1]
            out[i*4 + 2] = c[2]
            out[i*4 + 3] = c[3]

        return out_len * 4
