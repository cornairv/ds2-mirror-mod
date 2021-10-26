hkRenderGlowFilter PROTO C

.code
hkRenderGlowFilterTrampoline PROC public
	push rax
	push rbx
	push rcx
	push rdx
	push r8
	push r9

	mov rcx, qword ptr [r15]
	mov rcx, qword ptr [rcx + 8]
	mov rcx, qword ptr [rcx]
	mov rax, hkRenderGlowFilter
	call rax


	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rbx
	pop rax
	nop
hkRenderGlowFilterTrampoline ENDP

end