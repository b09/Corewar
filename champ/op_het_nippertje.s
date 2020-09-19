.name "Nippertje"
.comment "Dress me slowly, cause I'm in a Spanish hurry."

	sti		r1, %:live, %1
	sti		r1, %:live2, %1
	live	%-1
	sub		r1, r1, r2
fork:
	fork	%14
	fork	%-3
live2:
	live	%0
	zjmp	%:fork
	sub		r1, r1, r2
live:
	live	%0
	zjmp	%:live
