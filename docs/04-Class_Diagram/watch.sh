#!/bin/bash

feh --auto-reload 1 class_diagram.png &

inotifywait -m -e modify ./class_diagram.uml |
	while read filename; do
		plantuml $filename
	done

