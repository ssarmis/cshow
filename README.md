# How to build

- clone the repository
- run ```nmake -s```

# How to use

## Existing commands

- :borderless for deciding if the window is borderless
- :fullscreen for deciding if the window is in fullscreen
- :s is for marking the start of a slide
- :e is for marking the end of a slide
- :t for a simple text line
- :i for a simple image
- :b for setting the background (color/image) of the slide
- :vi for a simple video (avi/mp4 recomended) [currently bugged]
- :r for a simple colored rectangle
- :vX is for defining variables


## Usage

# :borderless w h
	- always the first line of the file
	- w and h are the width and the height of the window

# :fullscreen
	- always the first line of the file
	- no additional arguments required

# :s
	- always at the beginning of the slide

# :e
	- always at the end of the slide

# :t
	- :p the position
	- :b background color
	- :s size of the font
	- :f the font
	- :c color of the text	
	- "[text]" at the end of all arguments comes the text you want to display

# :i
	- :p the position
	- :s size of the image
	- "[path]" at the end of all arguments comes the path to the image

# :b
	- :c color of the slide background	

# :vi
	- :p the position
	- :s size of the video
	- "[path]" at the end of all arguments comes the path to the video

# :r
	- :p the position
	- :b rectangle color
	- :s size of the rectangle

# :vX name value/values
	- anywhere in the file
	- name represents the name of the variable
	- after the name comes the values you want to initialize the variable with
	- X can be replaced with the number of dimensions to initialize the variable with(max is 3)
	  e.g. :v3 myVar 10 25 0 is a vec3 variable named myVar and can now be used in parameters
	  like &myVar
	- the supported variable formats are :v, :v2, :v3
