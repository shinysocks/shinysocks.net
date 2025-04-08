.SILENT:
all:
	# compile index with ansi codes
	(cd ./public/static && bash make_index > index) 
	echo "compiled index for terminal queries."
	# run app with deno
	deno run -A src/app.js
