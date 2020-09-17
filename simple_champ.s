.name "Simple"
.comment ""

	ld		66, r2
	sti		r2, %:live, %1
live:
	live	%0
	ld		66, r2
