��    +      t  ;   �      �    �     �  !   �     �  7     R   ?  H   �     �  
   �     �  �        �     �     �     �     �  �     �   �     F     d     }     �     �  h   �  Q   !	  R   s	     �	     �	  =   �	  '   5
  '   ]
  .   �
  F   �
  B   �
  0   >  6   o      �     �  "   �     �          &  �  B  +  �     �  '        ,  0   @  Y   q  T   �        
   >     I  �   h       #        A     X     m  �   �  �   :  .   �     
     &     5  "   N  �   q  c   �  m   Y  '   �     �  >     -   F  2   t  8   �  S   �  R   4  1   �  <   �  ,   �     #  4   9     n      �  !   �        %              +   !                                     	             "                                           '   #      )          $   *            
                         (                &    %s appears to contain a %s filesystem which isn't known to reserve space for DOS-style boot.  Installing GRUB there could result in FILESYSTEM DESTRUCTION if valuable data is overwritten by grub-setup (--skip-fs-probe disables this check, use at your own risk) %s, with Linux %s %s, with Linux %s (recovery mode) %s, with kFreeBSD %s - Last modification time %d-%02d-%02d %02d:%02d:%02d %s Attempting to install GRUB to a partition instead of the MBR.  This is a BAD idea. Attempting to install GRUB to a partitionless disk.  This is a BAD idea. Booting a command list Device %s: ESC at any time exits. Embedding is not possible.  GRUB can only be installed in this setup by using blocklists.  However, blocklists are UNRELIABLE and its use is discouraged. FILE Filesystem cannot be accessed Filesystem type %s GNU GRUB  version %s Invalid device `%s'.
 Minimal BASH-like line editing is supported. For the first word, TAB lists possible command completions. Anywhere else TAB lists possible device or file completions. %s Minimum Emacs-like screen editing is supported. TAB lists completions. Press Ctrl-x to boot, Ctrl-c for a command-line or ESC to return menu. No DOS-style partitions found No device is specified.
 Partition %s: Partition table Press any key to continue... Press enter to boot the selected OS, 'e' to edit the commands before booting or 'c' for a command-line.
 This GPT partition label has no BIOS Boot Partition; embedding won't be possible! This msdos-style partition label has no post-MBR gap; embedding won't be possible! Unknown extra argument `%s'.
 Unknown filesystem Use the %C and %C keys to select which entry is highlighted.
 Warning: invalid background color `%s'
 Warning: invalid foreground color `%s'
 Warning: syntax error (missing slash) in `%s'
 Your core.img is unusually large.  It won't fit in the embedding area. Your embedding area is unusually small.  core.img won't fit in it. attempting to read the core image `%s' from GRUB attempting to read the core image `%s' from GRUB again cannot compress the kernel image cannot open %s diskboot.img size must be %u bytes prefix is too long the core image is too big the core image is too small Project-Id-Version: grub-1.97+20091221
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2011-11-24 14:53+0800
PO-Revision-Date: 2010-01-05 19:28+0100
Last-Translator: Milo Casagrande <milo@casagrande.name>
Language-Team: Italian <tp@lists.linux.it>
Language: it
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
 Sembra che %s contenga un file system %s, noto per non riservare dello spazio per l'avvio in stile DOS. Installare GRUB qui potrebbe portare alla DISTRUZIONE del file system se dati importanti vengono sovrascritti da grub-setup (--skip-fs-probe disabilita questo controllo, usare a proprio rischio). %s, con Linux %s %s, con Linux %s (modalità ripristino) %s, con kFreeBSD %s - Ultima modifica %d-%02d-%02d %02d.%02d.%02d %s Tentativo di installare GRUB in una partizione invece che nel MBR. Non è una buona idea. Tentativo di installare GRUB su un disco privo di partizioni. Non è una buona idea. Avvio di un elenco di comandi Device %s: ESC esce in qualsiasi momento. L'embed non è possibile. GRUB può essere installato con questa configurazione solo usando blocklist. Le blocklist non sono comunque affidabili e ne viene sconsigliato l'uso. FILE Impossibile accedere al file system File system di tipo %s GNU GRUB versione %s Device "%s" non valido.
 Supporto minimale per modifica in stile BASH. Per la prima parola, TAB elenca i completamenti del comando. In altre parti elenca i device possibili o il completamento dei file. %s Supporto minimale per modifica in stile Emacs. TAB elenca i completamenti. Premere Ctrl-X per avviare, Ctrl-C per la riga di comando o Esc per tornare al menù. Non sono state trovate partizioni in stile DOS Nessun device specificato.
 Partizione %s: Tabella delle partizioni Premere un tasto per continuare... Premere Invio per avviare il sistema selezionato, "e" per modificare i comandi prima dell'avvio oppure "c" per la riga di comando.
 L'etichetta della partizione GPT non presenta una BIOS Boot Partition; l'embed non sarà possibile. L'etichetta della partizione in stile MS-DOS non presenta uno spazio dopo l'MBR; l'embed non sarà possibile. Argomento aggiuntivo "%s" sconosciuto.
 File system sconosciuto Usare i tasti %C e %C per selezionare la voce da evidenziare.
 Attenzione: colore di sfondo "%s" non valido
 Attenzione: colore di primo piano "%s" non valido
 Attenzione: errore di sintassi (slash mancante) in "%s"
 L'immagine core.img è troppo grande. Non può essere contenuta nell'area di embed. L'area di embed è troppo piccola. L'immagine core.img non può esservi contenuta. tentativo di leggere l'immagine core "%s" da GRUB tentativo di leggere nuovamente l'immagine core "%s" da GRUB impossibile comprimere l'immagine del kernel impossibile aprire %s la dimensione di diskboot.img deve essere di %u byte il prefisso è troppo lungo l'immagine core è troppo grande l'immagine core è troppo piccola 