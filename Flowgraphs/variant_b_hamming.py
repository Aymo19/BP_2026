#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: MPSK channel with Noise and Hamming Encoding
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
import variant_b_hamming_epy_block_0 as epy_block_0  # embedded python block
import variant_b_hamming_epy_block_1 as epy_block_1  # embedded python block
import variant_b_hamming_modulation_config as modulation_config  # embedded python module



class variant_b_hamming(gr.top_block, Qt.QWidget):

    def __init__(self, modulation_name='QPSK'):
        gr.top_block.__init__(self, "MPSK channel with Noise and Hamming Encoding", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("MPSK channel with Noise and Hamming Encoding")
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

        self.settings = Qt.QSettings("GNU Radio", "variant_b_hamming")

        try:
            geometry = self.settings.value("geometry")
            if geometry:
                self.restoreGeometry(geometry)
        except BaseException as exc:
            print(f"Qt GUI: Could not restore geometry: {str(exc)}", file=sys.stderr)

        ##################################################
        # Parameters
        ##################################################
        self.modulation_name = modulation_name

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000
        self.modulation = modulation = digital.constellation_bpsk().base()
        self.modulation.set_npwr(1.0)
        self.N = N = 2
        self.Modulacia = Modulacia = digital.constellation_bpsk().base()
        self.Modulacia.set_npwr(1.0)

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_vector_sink_f_0_0 = qtgui.vector_sink_f(
            256,
            0,
            (float(15) / float(256 - 1)),
            "Eb/N0 [dB]",
            "log Pb",
            "BER",
            1, # Number of inputs
            None # parent
        )
        self.qtgui_vector_sink_f_0_0.set_update_time(0.1)
        self.qtgui_vector_sink_f_0_0.set_y_axis((-6), 0)
        self.qtgui_vector_sink_f_0_0.enable_autoscale(False)
        self.qtgui_vector_sink_f_0_0.enable_grid(True)
        self.qtgui_vector_sink_f_0_0.set_x_axis_units("dB")
        self.qtgui_vector_sink_f_0_0.set_y_axis_units("")
        self.qtgui_vector_sink_f_0_0.set_ref_level(0)


        labels = ["Simulácia HAMMING QPSK", '"Teoreticka GRAY QPSK', "Teoreticka QPSK", "Teoreticka 8PSK", "Teoreticka 16PSK",
            "Teoreticka 16QAM", "Teoreticka 32QAM", "Teoreticka 64QAM", "Teoreticka 128QAM", "Teoreticka 256QAM"]
        widths = [2, 2, 2, 2, 2,
            2, 2, 2, 2, 2]
        colors = ["red", "blue", "blue", "green", "black",
            "yellow", "dark blue", "dark red", "dark green", "red"]
        alphas = [1, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
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
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            1024, #size
            "", #name
            2, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis((-2), 2)
        self.qtgui_const_sink_x_0.set_x_axis((-2), 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(False)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_const_sink_x_0_win)
        self.epy_block_1 = epy_block_1.blk()
        self.epy_block_0 = epy_block_0.blk()
        self.digital_constellation_encoder_bc_0 = digital.constellation_encoder_bc(Modulacia)
        self.digital_constellation_decoder_cb_0 = digital.constellation_decoder_cb(Modulacia)
        self.blocks_throttle2_0 = blocks.throttle( gr.sizeof_gr_complex*1, samp_rate, True, 0 if "auto" == "auto" else max( int(float(0.1) * samp_rate) if "auto" == "time" else int(0.1), 1) )
        self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_float*1, 256)
        self.blocks_stream_mux_1 = blocks.stream_mux(gr.sizeof_char*1, [1]*4)
        self.blocks_stream_mux_0 = blocks.stream_mux(gr.sizeof_char*1, [1]*7)
        self.blocks_stream_demux_1 = blocks.stream_demux(gr.sizeof_char*1, [1]*7)
        self.blocks_stream_demux_0 = blocks.stream_demux(gr.sizeof_char*1, [1] * 4)
        self.blocks_repack_bits_bb_0_1 = blocks.repack_bits_bb(1, modulation.bits_per_symbol(), "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0_0_0 = blocks.repack_bits_bb(modulation.bits_per_symbol(), 1, "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0_0 = blocks.repack_bits_bb(modulation.bits_per_symbol(), 1, "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0 = blocks.repack_bits_bb(1, modulation.bits_per_symbol(), "", False, gr.GR_LSB_FIRST)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_char*1)
        self.blocks_nlog10_ff_0 = blocks.nlog10_ff(1, 1, 0)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, N, 10000))), True)
        self.ErTools_MC_0 = ErTools.MC(256, 0, 15)
        self.ErTools_BER_0 = ErTools.BER(256, N)
        self.ErTools_AWGN_0 = ErTools.AWGN(N)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.ErTools_AWGN_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.ErTools_BER_0, 0), (self.blocks_nlog10_ff_0, 0))
        self.connect((self.ErTools_MC_0, 0), (self.ErTools_AWGN_0, 1))
        self.connect((self.ErTools_MC_0, 1), (self.ErTools_BER_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.ErTools_BER_0, 2))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_repack_bits_bb_0_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.digital_constellation_decoder_cb_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.blocks_nlog10_ff_0, 0), (self.blocks_stream_to_vector_0, 0))
        self.connect((self.blocks_repack_bits_bb_0, 0), (self.digital_constellation_encoder_bc_0, 0))
        self.connect((self.blocks_repack_bits_bb_0_0, 0), (self.blocks_stream_demux_0, 0))
        self.connect((self.blocks_repack_bits_bb_0_0_0, 0), (self.blocks_stream_demux_1, 0))
        self.connect((self.blocks_repack_bits_bb_0_1, 0), (self.ErTools_BER_0, 1))
        self.connect((self.blocks_repack_bits_bb_0_1, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.blocks_stream_demux_0, 1), (self.epy_block_0, 1))
        self.connect((self.blocks_stream_demux_0, 3), (self.epy_block_0, 3))
        self.connect((self.blocks_stream_demux_0, 0), (self.epy_block_0, 0))
        self.connect((self.blocks_stream_demux_0, 2), (self.epy_block_0, 2))
        self.connect((self.blocks_stream_demux_1, 0), (self.epy_block_1, 0))
        self.connect((self.blocks_stream_demux_1, 4), (self.epy_block_1, 4))
        self.connect((self.blocks_stream_demux_1, 3), (self.epy_block_1, 3))
        self.connect((self.blocks_stream_demux_1, 1), (self.epy_block_1, 1))
        self.connect((self.blocks_stream_demux_1, 6), (self.epy_block_1, 6))
        self.connect((self.blocks_stream_demux_1, 2), (self.epy_block_1, 2))
        self.connect((self.blocks_stream_demux_1, 5), (self.epy_block_1, 5))
        self.connect((self.blocks_stream_mux_0, 0), (self.blocks_repack_bits_bb_0, 0))
        self.connect((self.blocks_stream_mux_1, 0), (self.blocks_repack_bits_bb_0_1, 0))
        self.connect((self.blocks_stream_to_vector_0, 0), (self.qtgui_vector_sink_f_0_0, 0))
        self.connect((self.blocks_throttle2_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.blocks_repack_bits_bb_0_0_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.ErTools_AWGN_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.blocks_throttle2_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.qtgui_const_sink_x_0, 1))
        self.connect((self.epy_block_0, 0), (self.blocks_stream_mux_0, 0))
        self.connect((self.epy_block_0, 3), (self.blocks_stream_mux_0, 3))
        self.connect((self.epy_block_0, 4), (self.blocks_stream_mux_0, 4))
        self.connect((self.epy_block_0, 2), (self.blocks_stream_mux_0, 2))
        self.connect((self.epy_block_0, 6), (self.blocks_stream_mux_0, 6))
        self.connect((self.epy_block_0, 1), (self.blocks_stream_mux_0, 1))
        self.connect((self.epy_block_0, 5), (self.blocks_stream_mux_0, 5))
        self.connect((self.epy_block_1, 1), (self.blocks_stream_mux_1, 1))
        self.connect((self.epy_block_1, 0), (self.blocks_stream_mux_1, 0))
        self.connect((self.epy_block_1, 3), (self.blocks_stream_mux_1, 3))
        self.connect((self.epy_block_1, 2), (self.blocks_stream_mux_1, 2))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "variant_b_hamming")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_modulation_name(self):
        return self.modulation_name

    def set_modulation_name(self, modulation_name):
        self.modulation_name = modulation_name

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle2_0.set_sample_rate(self.samp_rate)

    def get_modulation(self):
        return self.modulation

    def set_modulation(self, modulation):
        self.modulation = modulation

    def get_N(self):
        return self.N

    def set_N(self, N):
        self.N = N

    def get_Modulacia(self):
        return self.Modulacia

    def set_Modulacia(self, Modulacia):
        self.Modulacia = Modulacia
        self.digital_constellation_decoder_cb_0.set_constellation(self.Modulacia)
        self.digital_constellation_encoder_bc_0.set_constellation(self.Modulacia)



def argument_parser():
    parser = ArgumentParser()
    parser.add_argument(
        "--modulation-name", dest="modulation_name", type=str, default='QPSK',
        help="Set Modulation Name [default=%(default)r]")
    return parser


def main(top_block_cls=variant_b_hamming, options=None):
    if options is None:
        options = argument_parser().parse_args()

    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls(modulation_name=options.modulation_name)

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
