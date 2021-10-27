EXTERN hkRenderGlowFilter: PROC

_TEXT SEGMENT

hkRenderGlowFilterTrampoline PROC
	push rax
	push rcx
	push rdx
	push r8
	push r9
	push r10
	push r11
	sub rsp, 40

	lea rcx, [rbp + 40h]
	mov rcx, qword ptr [rcx + 8]
	mov rcx, qword ptr [rcx]
	mov rax, hkRenderGlowFilter
	call rax

	add rsp, 40
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rax
	nop
hkRenderGlowFilterTrampoline ENDP

_TEXT ENDS

END