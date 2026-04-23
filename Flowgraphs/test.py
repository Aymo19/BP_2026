#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.10.9.2

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio import ErTools
from gnuradio import blocks
import numpy
from gnuradio import digital
from gnuradio import gr
from gnuradio.filter import firdes
from gnuradio.fft import window
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
import sip



class test(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Not titled yet")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except BaseException as exc:
            print(f"Qt GUI: Could not set Icon: {str(exc)}", file=sys.stderr)
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "test")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Variables
        ##################################################
        self.M = M = 256
        self.samp_rate = samp_rate = int(10e6)
        self.Num_samp = Num_samp = int(10e6)
        self.N = N = 256
        self.Modulacia_1 = Modulacia_1 = digital.constellation_bpsk().base()
        self.Modulacia_1.set_npwr(1.0)
        self.Modulacia = Modulacia = digital.qam.qam_constellation(constellation_points=M, differential=False, mod_code="gray", large_ampls_to_corners=False)
        self.EbN0_min = EbN0_min = 0
        self.EbN0_max = EbN0_max = 25

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_vector_sink_f_0_0 = qtgui.vector_sink_f(
            N,
            0,
            (float(EbN0_max - EbN0_min) / float(N - 1)),
            "Eb/N0 [dB]",
            "log Pb",
            "BER",
            2, # Number of inputs
            None # parent
        )
        self.qtgui_vector_sink_f_0_0.set_update_time(0.1)
        self.qtgui_vector_sink_f_0_0.set_y_axis((-6), 0)
        self.qtgui_vector_sink_f_0_0.enable_autoscale(False)
        self.qtgui_vector_sink_f_0_0.enable_grid(True)
        self.qtgui_vector_sink_f_0_0.set_x_axis_units("dB")
        self.qtgui_vector_sink_f_0_0.set_y_axis_units("")
        self.qtgui_vector_sink_f_0_0.set_ref_level(0)


        labels = ["Simulácia 256-QAM", "Teoretická 256-QAM", "Simulácia 16-QAM", "Teoreticka BPSK", "Teoreticka 8PSK",
            "Teoreticka 16-QAM", "Teoreticka 32QAM", "Teoreticka 64QAM", "Teoreticka 128QAM", "Teoreticka 256QAM"]
        widths = [2, 2, 2, 2, 2,
            2, 2, 2, 2, 2]
        colors = ["red", "blue", "green", "cyan", "black",
            "yellow", "dark blue", "dark red", "dark green", "red"]
        alphas = [1, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_vector_sink_f_0_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_vector_sink_f_0_0.set_line_label(i, labels[i])
            self.qtgui_vector_sink_f_0_0.set_line_width(i, widths[i])
            self.qtgui_vector_sink_f_0_0.set_line_color(i, colors[i])
            self.qtgui_vector_sink_f_0_0.set_line_alpha(i, alphas[i])

        self._qtgui_vector_sink_f_0_0_win = sip.wrapinstance(self.qtgui_vector_sink_f_0_0.qwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_vector_sink_f_0_0_win, 2, 0, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.digital_constellation_encoder_bc_0 = digital.constellation_encoder_bc(Modulacia)
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(Modulacia)
        self.blocks_throttle2_0 = blocks.throttle( gr.sizeof_gr_complex*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_stream_to_vector_0_1_0 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_nlog10_ff_0_1_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, M, Num_samp))), True)
        self.ErTools_Teoreticka_BER_0 = ErTools.Teoreticka_BER(N, M, 'QAM', EbN0_min, EbN0_max)
        self.ErTools_MC_0 = ErTools.MC(N, EbN0_min, EbN0_max)
        self.ErTools_BER_0 = ErTools.BER(N, M)
        self.ErTools_AWGN_0 = ErTools.AWGN(M, 1, 1)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.ErTools_AWGN_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.ErTools_BER_0, 0), (self.blocks_nlog10_ff_0, 0))
        self.connect((self.ErTools_MC_0, 0), (self.ErTools_AWGN_0, 1))
        self.connect((self.ErTools_MC_0, 1), (self.ErTools_BER_0, 0))
        self.connect((self.ErTools_Teoreticka_BER_0, 0), (self.blocks_nlog10_ff_0_1_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.ErTools_BER_0, 1))
        self.connect((self.analog_random_source_x_0, 0), (self.digital_constellation_encoder_bc_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.digital_constellation_decoder_cb_0, 0))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.blocks_stream_to_vector_0, 0))
        self.connect((self.blocks_nlog10_ff_0_1_0, 0), (self.blocks_stream_to_vector_0_1_0, 0))
        self.connect((self.blocks_stream_to_vector_0, 0), (self.qtgui_vector_sink_f_0_0, 0))
        self.connect((self.blocks_stream_to_vector_0_1_0, 0), (self.qtgui_vector_sink_f_0_0, 1))
        self.connect((self.blocks_throttle2_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.ErTools_BER_0, 2))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.ErTools_AWGN_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.blocks_throttle2_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "test")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_M(self):
        return self.M

    def set_M(self, M):
        self.M = M
        self.set_Modulacia(digital.qam.qam_constellation(constellation_points=self.M, differential=False, mod_code="gray", large_ampls_to_corners=False))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle2_0.set_sample_rate(self.samp_rate)

    def get_Num_samp(self):
        return self.Num_samp

    def set_Num_samp(self, Num_samp):
        self.Num_samp = Num_samp

    def get_N(self):
        return self.N

    def set_N(self, N):
        self.N = N
        self.qtgui_vector_sink_f_0_0.set_x_axis(0, (float(self.EbN0_max - self.EbN0_min) / float(self.N - 1)))

    def get_Modulacia_1(self):
        return self.Modulacia_1

    def set_Modulacia_1(self, Modulacia_1):
        self.Modulacia_1 = Modulacia_1

    def get_Modulacia(self):
        return self.Modulacia

    def set_Modulacia(self, Modulacia):
        self.Modulacia = Modulacia
        self.digital_constellation_decoder_cb_0.set_constellation(self.Modulacia)
        self.digital_constellation_encoder_bc_0.set_constellation(self.Modulacia)

    def get_EbN0_min(self):
        return self.EbN0_min

    def set_EbN0_min(self, EbN0_min):
        self.EbN0_min = EbN0_min
        self.qtgui_vector_sink_f_0_0.set_x_axis(0, (float(self.EbN0_max - self.EbN0_min) / float(self.N - 1)))

    def get_EbN0_max(self):
        return self.EbN0_max

    def set_EbN0_max(self, EbN0_max):
        self.EbN0_max = EbN0_max
        self.qtgui_vector_sink_f_0_0.set_x_axis(0, (float(self.EbN0_max - self.EbN0_min) / float(self.N - 1)))




def main(top_block_cls=test, options=None):

    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
