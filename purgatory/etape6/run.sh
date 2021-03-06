#!/usr/bin/env bash
ls && mkdir build -p && cd build && cmake .. && make && cd .. && ls && valgrind ./build/test_improved_pattern && dot -Tpdf mechant.dot -o mechant.pdf && dot -Tpdf union1.dot -o union1.pdf && dot -Tpdf union2.dot -o union2.pdf && dot -Tpdf concat.dot -o concat.pdf

