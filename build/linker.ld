ENTRY(kernel_main)

SECTIONS {
	.text : { *(.text) }
	.data : { *(.data) }
	.bss  : { *(.bss) }
}
