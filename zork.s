.name "ZORK"
.comment ""

	sti		r1, %:live, %1
	and		r1, %0, r2
live:
	live	%1
	zjmp	%:live
