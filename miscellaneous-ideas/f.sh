#!/bin/bash

# Regular expression for ANY function definition 

grep -E ^[int,void,off_t].* ?{ ?$ $1

# grep -E ^[void, char, int, long]{1} +\( ... enhance it
