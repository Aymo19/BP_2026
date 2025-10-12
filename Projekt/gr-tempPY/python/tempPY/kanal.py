#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2025 Marek Hetteš.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

import numpy
import numpy as np
import random
import math

from gnuradio import gr

class kanal(gr.sync_block):
    """
    docstring for block kanal
    """
        def __init__(self, N=8, EsN0min=0, EsN0max=16, B=100, Rs=1):
        gr.sync_block.__init__(self,
            name="kanal",
            in_sig=[np.complex64, ],
            out_sig=[np.complex64, np.int32]
        )
        self.N = N
        self.B = B
        self.Rs = Rs

        self.EsN0dB = np.linspace(EsN0min, EsN0max, N)
        self.k = 0


    def work(self, input_items, output_items):
        L = len(input_items[0])
        Rs = self.Rs
        B1 = self.B
        Pin = np.mean(np.absolute(input_items[0])**2)

        for i in range(0, L):
            output_items[0][i] = input_items[0][i] + \
                noise_c(self.EsN0dB[self.k], Pin, Rs, B1)
            output_items[1][i] = self.k
            if self.k < self.N-1:
                self.k += 1
            else:
                self.k = 0
        return len(output_items[0])

def noise_c(EsN0_dB, P_s, Rs, B):
    EsN0 = pow(10., EsN0_dB/10.)
    SNR = EsN0*Rs/B
    P_n = P_s/SNR
    Vrms = math.sqrt(P_n)
    Vrms_q = Vrms/math.sqrt(2.)
    n = np.random.normal(0., Vrms_q)+np.random.normal(0., Vrms_q)*1.j

    return n

