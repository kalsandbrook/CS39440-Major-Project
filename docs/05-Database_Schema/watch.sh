feh --auto-reload 1 database_schema.png &

inotifywait -m -e modify ./database_schema.uml |
	while read filename; do
		plantuml $filename
	done

