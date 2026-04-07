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
        self.samp_rate = samp_rate = 1e6
        self.modulation = modulation = digital.constellation_bpsk().base()
        self.modulation.set_npwr(1.0)
        self.Modulacia = Modulacia = digital.constellation_qpsk().base()
        self.Modulacia.set_npwr(1.0)

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
            1024, #size
            samp_rate, #samp_rate
            "", #name
            2, #number of inputs
            None # parent
        )
        self.qtgui_time_sink_x_0.set_update_time(5)
        self.qtgui_time_sink_x_0.set_y_axis(-1, 2)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(True)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)


        labels = ['Signal 1', 'Signal 2', 'Signal 3', 'Signal 4', 'Signal 5',
            'Signal 6', 'Signal 7', 'Signal 8', 'Signal 9', 'Signal 10']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ['blue', 'red', 'green', 'black', 'cyan',
            'magenta', 'yellow', 'dark red', 'dark green', 'dark blue']
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]
        styles = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1]


        for i in range(2):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_win)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title("")

        labels = ['', '', '', '', '',
            '', '', '', '', '']
        units = ['', '', '', '', '',
            '', '', '', '', '']
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0.set_min(i, -1)
            self.qtgui_number_sink_0.set_max(i, 256)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_number_sink_0_win)
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
        self.blocks_stream_mux_1 = blocks.stream_mux(gr.sizeof_char*1, [1]*4)
        self.blocks_stream_mux_0 = blocks.stream_mux(gr.sizeof_char*1, [1]*7)
        self.blocks_stream_demux_1 = blocks.stream_demux(gr.sizeof_char*1, [1]*7)
        self.blocks_stream_demux_0 = blocks.stream_demux(gr.sizeof_char*1, [1] * 4)
        self.blocks_repack_bits_bb_0_1 = blocks.repack_bits_bb(1, modulation.bits_per_symbol(), "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0_0_0 = blocks.repack_bits_bb(modulation.bits_per_symbol(), 1, "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0_0 = blocks.repack_bits_bb(modulation.bits_per_symbol(), 1, "", False, gr.GR_LSB_FIRST)
        self.blocks_repack_bits_bb_0 = blocks.repack_bits_bb(1, modulation.bits_per_symbol(), "", False, gr.GR_LSB_FIRST)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_char*1)
        self.blocks_int_to_float_0 = blocks.int_to_float(1, 1)
        self.blocks_char_to_float_1_0 = blocks.char_to_float(1, 1)
        self.blocks_char_to_float_1 = blocks.char_to_float(1, 1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, 2, 10000))), True)
        self.ErTools_AWGN_0 = ErTools.AWGN(256, 4, 0, 15)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.ErTools_AWGN_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.ErTools_AWGN_0, 1), (self.blocks_int_to_float_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_char_to_float_1_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_repack_bits_bb_0_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.digital_constellation_decoder_cb_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.blocks_char_to_float_1, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.blocks_char_to_float_1_0, 0), (self.qtgui_time_sink_x_0, 1))
        self.connect((self.blocks_int_to_float_0, 0), (self.qtgui_number_sink_0, 0))
        self.connect((self.blocks_repack_bits_bb_0, 0), (self.digital_constellation_encoder_bc_0, 0))
        self.connect((self.blocks_repack_bits_bb_0_0, 0), (self.blocks_stream_demux_0, 0))
        self.connect((self.blocks_repack_bits_bb_0_0_0, 0), (self.blocks_stream_demux_1, 0))
        self.connect((self.blocks_repack_bits_bb_0_1, 0), (self.blocks_char_to_float_1, 0))
        self.connect((self.blocks_repack_bits_bb_0_1, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.blocks_stream_demux_0, 0), (self.epy_block_0, 0))
        self.connect((self.blocks_stream_demux_0, 2), (self.epy_block_0, 2))
        self.connect((self.blocks_stream_demux_0, 3), (self.epy_block_0, 3))
        self.connect((self.blocks_stream_demux_0, 1), (self.epy_block_0, 1))
        self.connect((self.blocks_stream_demux_1, 3), (self.epy_block_1, 3))
        self.connect((self.blocks_stream_demux_1, 2), (self.epy_block_1, 2))
        self.connect((self.blocks_stream_demux_1, 6), (self.epy_block_1, 6))
        self.connect((self.blocks_stream_demux_1, 5), (self.epy_block_1, 5))
        self.connect((self.blocks_stream_demux_1, 1), (self.epy_block_1, 1))
        self.connect((self.blocks_stream_demux_1, 4), (self.epy_block_1, 4))
        self.connect((self.blocks_stream_demux_1, 0), (self.epy_block_1, 0))
        self.connect((self.blocks_stream_mux_0, 0), (self.blocks_repack_bits_bb_0, 0))
        self.connect((self.blocks_stream_mux_1, 0), (self.blocks_repack_bits_bb_0_1, 0))
        self.connect((self.blocks_throttle2_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0, 0), (self.blocks_repack_bits_bb_0_0_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.ErTools_AWGN_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.blocks_throttle2_0, 0))
        self.connect((self.digital_constellation_encoder_bc_0, 0), (self.qtgui_const_sink_x_0, 1))
        self.connect((self.epy_block_0, 2), (self.blocks_stream_mux_0, 2))
        self.connect((self.epy_block_0, 0), (self.blocks_stream_mux_0, 0))
        self.connect((self.epy_block_0, 1), (self.blocks_stream_mux_0, 1))
        self.connect((self.epy_block_0, 5), (self.blocks_stream_mux_0, 5))
        self.connect((self.epy_block_0, 6), (self.blocks_stream_mux_0, 6))
        self.connect((self.epy_block_0, 3), (self.blocks_stream_mux_0, 3))
        self.connect((self.epy_block_0, 4), (self.blocks_stream_mux_0, 4))
        self.connect((self.epy_block_1, 0), (self.blocks_stream_mux_1, 0))
        self.connect((self.epy_block_1, 3), (self.blocks_stream_mux_1, 3))
        self.connect((self.epy_block_1, 2), (self.blocks_stream_mux_1, 2))
        self.connect((self.epy_block_1, 1), (self.blocks_stream_mux_1, 1))


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
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)

    def get_modulation(self):
        return self.modulation

    def set_modulation(self, modulation):
        self.modulation = modulation

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
