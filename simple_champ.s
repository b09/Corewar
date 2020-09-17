.name "Simple"
.comment ""

	ld		4, r2
	sti		r2, %:live, %1
live:
	live	%0
	ld		%12, r3
	ld		%10, r4
	add		r4, r3, r5
	st		r5, 5
	sub		r4, r4, r4
	zjmp	%:live
