
.section .text
.global _myentry
_myentry:
        # jump to the real entry 
        j _entry
