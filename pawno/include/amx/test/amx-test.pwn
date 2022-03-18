#include <a_samp>

#include "..\amx"

main() {
	// This must output "1".
	printf("%d", ReadAmxCell(AMX_OFFSET_BASE) == GetAmxBaseAddress());
}
