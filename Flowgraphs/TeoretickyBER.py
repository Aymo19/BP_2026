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



class TeoretickyBER(gr.top_block, Qt.QWidget):

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

        self.settings = Qt.QSettings("GNU Radio", "TeoretickyBER")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.SNR_min = SNR_min = 0
        self.SNR_max = SNR_max = 50
        self.N = N = 256

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_vector_sink_f_0 = qtgui.vector_sink_f(
            N,
            0,
            0.196850394,
            "Eb/N0 [dB]",
            "Pb",
            "BER",
            4, # Number of inputs
            None # parent
        )
        self.qtgui_vector_sink_f_0.set_update_time(0.01)
        self.qtgui_vector_sink_f_0.set_y_axis((-6), 1)
        self.qtgui_vector_sink_f_0.enable_autoscale(False)
        self.qtgui_vector_sink_f_0.enable_grid(True)
        self.qtgui_vector_sink_f_0.set_x_axis_units("")
        self.qtgui_vector_sink_f_0.set_y_axis_units("")
        self.qtgui_vector_sink_f_0.set_ref_level(0)


        labels = ["16-QAM", "64-QAM", "256-QAM", "1024-QAM", '',
            '', '', '', '', '']
        widths = [2, 2, 2, 2, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(4):
            if len(labels[i]) == 0:
                self.qtgui_vector_sink_f_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_vector_sink_f_0.set_line_label(i, labels[i])
            self.qtgui_vector_sink_f_0.set_line_width(i, widths[i])
            self.qtgui_vector_sink_f_0.set_line_color(i, colors[i])
            self.qtgui_vector_sink_f_0.set_line_alpha(i, alphas[i])

        self._qtgui_vector_sink_f_0_win = sip.wrapinstance(self.qtgui_vector_sink_f_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_vector_sink_f_0_win)
        self.blocks_throttle2_0_2 = blocks.throttle( gr.sizeof_float*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_throttle2_0_1 = blocks.throttle( gr.sizeof_float*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_throttle2_0_0 = blocks.throttle( gr.sizeof_float*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_throttle2_0 = blocks.throttle( gr.sizeof_float*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_stream_to_vector_0_2 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_stream_to_vector_0_1 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_stream_to_vector_0_0 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_float*1, N)
        self.blocks_nlog10_ff_0_2 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0_1 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_nlog10_ff_0 = blocks.nlog10_ff(1, 1, 0)
        self.ErTools_Teoreticka_BER_0_2 = ErTools.Teoreticka_BER(N, 8192, 'QAM', 0, SNR_max)
        self.ErTools_Teoreticka_BER_0_1 = ErTools.Teoreticka_BER(N, 256, 'QAM', 0, SNR_max)
        self.ErTools_Teoreticka_BER_0_0 = ErTools.Teoreticka_BER(N, 64, 'QAM', 0, SNR_max)
        self.ErTools_Teoreticka_BER_0 = ErTools.Teoreticka_BER(N, 16, 'QAM', 0, SNR_max)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.ErTools_Teoreticka_BER_0, 0), (self.blocks_throttle2_0, 0))
        self.connect((self.ErTools_Teoreticka_BER_0_0, 0), (self.blocks_throttle2_0_0, 0))
        self.connect((self.ErTools_Teoreticka_BER_0_1, 0), (self.blocks_throttle2_0_1, 0))
        self.connect((self.ErTools_Teoreticka_BER_0_2, 0), (self.blocks_throttle2_0_2, 0))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.blocks_stream_to_vector_0, 0))
        self.connect((self.blocks_nlog10_ff_0_0, 0), (self.blocks_stream_to_vector_0_0, 0))
        self.connect((self.blocks_nlog10_ff_0_1, 0), (self.blocks_stream_to_vector_0_1, 0))
        self.connect((self.blocks_nlog10_ff_0_2, 0), (self.blocks_stream_to_vector_0_2, 0))
        self.connect((self.blocks_stream_to_vector_0, 0), (self.qtgui_vector_sink_f_0, 0))
        self.connect((self.blocks_stream_to_vector_0_0, 0), (self.qtgui_vector_sink_f_0, 1))
        self.connect((self.blocks_stream_to_vector_0_1, 0), (self.qtgui_vector_sink_f_0, 2))
        self.connect((self.blocks_stream_to_vector_0_2, 0), (self.qtgui_vector_sink_f_0, 3))
        self.connect((self.blocks_throttle2_0, 0), (self.blocks_nlog10_ff_0, 0))
        self.connect((self.blocks_throttle2_0_0, 0), (self.blocks_nlog10_ff_0_0, 0))
        self.connect((self.blocks_throttle2_0_1, 0), (self.blocks_nlog10_ff_0_1, 0))
        self.connect((self.blocks_throttle2_0_2, 0), (self.blocks_nlog10_ff_0_2, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "TeoretickyBER")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle2_0.set_sample_rate(self.samp_rate)
        self.blocks_throttle2_0_0.set_sample_rate(self.samp_rate)
        self.blocks_throttle2_0_1.set_sample_rate(self.samp_rate)
        self.blocks_throttle2_0_2.set_sample_rate(self.samp_rate)

    def get_SNR_min(self):
        return self.SNR_min

    def set_SNR_min(self, SNR_min):
        self.SNR_min = SNR_min

    def get_SNR_max(self):
        return self.SNR_max

    def set_SNR_max(self, SNR_max):
        self.SNR_max = SNR_max

    def get_N(self):
        return self.N

    def set_N(self, N):
        self.N = N




def main(top_block_cls=TeoretickyBER, options=None):

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
