case '\'': fputs("\\'", f); break;
case '"': fputs("\\\"", f); break;
default:
if (0x20 <= c && c <= 0x7f)
	putc(c, f);
	else
	fprintf(f, "\\x%02x", c);
	}
}
putc('"', f);

