��          �   %   �      0    1     6  !   H     j  R     H   �  �        �     �     �  Q     R   T     �  F   �  B     0   O  6   �      �     �  "   �     
          7  \  S  R  �     
     
     4
  [   H
  T   �
  �   �
     �  #   �     �  R     X   V  !   �  Q   �  M   #  3   q  ;   �  2   �       '   '     O     f     �                                                   
         	                                                                   %s appears to contain a %s filesystem which isn't known to reserve space for DOS-style boot.  Installing GRUB there could result in FILESYSTEM DESTRUCTION if valuable data is overwritten by grub-setup (--skip-fs-probe disables this check, use at your own risk) %s, with Linux %s %s, with Linux %s (recovery mode) %s, with kFreeBSD %s Attempting to install GRUB to a partition instead of the MBR.  This is a BAD idea. Attempting to install GRUB to a partitionless disk.  This is a BAD idea. Embedding is not possible.  GRUB can only be installed in this setup by using blocklists.  However, blocklists are UNRELIABLE and its use is discouraged. Invalid device `%s'.
 No DOS-style partitions found No device is specified.
 This GPT partition label has no BIOS Boot Partition; embedding won't be possible! This msdos-style partition label has no post-MBR gap; embedding won't be possible! Unknown extra argument `%s'.
 Your core.img is unusually large.  It won't fit in the embedding area. Your embedding area is unusually small.  core.img won't fit in it. attempting to read the core image `%s' from GRUB attempting to read the core image `%s' from GRUB again cannot compress the kernel image cannot open %s diskboot.img size must be %u bytes prefix is too long the core image is too big the core image is too small Project-Id-Version: grub-1.97+20091122
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2011-11-24 14:53+0800
PO-Revision-Date: 2009-12-12 19:15+0100
Last-Translator: Erwin Poeze <erwin.poeze@gmail.com>
Language-Team: Dutch <vertaling@vrijschrift.org>
Language: nl
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 %s blijkt een %s-bestandssysteem te bevatten waarvan bekend is dat er geen ruimte voor DOS-achtig opstarten wordt gereserveerd. Installeren van GRUB daarin kan VERNIELING VAN HET BESTANDSSYSTEEM tot gevolg hebben als waardevolle gegevens worden overschreven door grub-setup (--skip-fs-probe schakelt deze controle uit, op uw eigen risico) %s, met Linux %s %s, met Linux %s (herstelmodus) %s, met kFreeBSD %s Poging om GRUB in een partitie te installeren in plaats van de MBR. Dit is een SLECHT idee. Poging om GRUB op een schijf zonder partitie te installeren. Dit is een SLECHT idee. Inbedden is niet mogelijk. GRUB kan in deze configuratie alleen worden geïnstalleerd met bloklijsten. Echter, bloklijsten zijn ONBETROUWBAAR en het gebruik ervan wordt ontraden. Ongeldig apparaat `%s'.
 Geen DOS-achtige partities gevonden Geen apparaat opgegeven.
 Dit GPT-partitielabel heeft geen BIOS opstartpartitie; inbedding is niet mogelijk! Dit MSDOS-achtige partitielabel heeft geen ruimte na de MBR; inbedding is niet mogelijk! Extra argument `%s' is onbekend.
 Uw core.img is ongebruikelijk groot.  Het zal niet in de inbeddingsruimte passen. Uw inbeddingsruimte is ongebruikelijk klein.  core.img zal er niet in passen. poging om de core-afbeelding `%s' uit GRUB te lezen poging om de core-afbeelding `%s' uit GRUB opnieuw te lezen de kernel-afbeelding kan niet worden gecomprimeerd kan %s niet openen grootte diskboot.img moet %u bytes zijn voorvoegsel is te lang de core-afbeelding is te groot de core-afbeelding is te klein 