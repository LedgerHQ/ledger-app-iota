#ifndef NANO_DISPLAY_H
#define NANO_DISPLAY_H

void display_main_menu(void);
void display_about(void);
void display_version(void);
void display_more_info(void);
void display_bip_path(void);
void display_addr(void);     // display pubkey on ledger
void display_addr_chk(void); // display abbrv with chk
void display_tx_addr(void);  // display address in tx
void display_prompt_tx(void);
void display_unknown_state(void);

#endif // NANO_DISPLAY_H
