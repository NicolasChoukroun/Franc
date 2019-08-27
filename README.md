# Franc "The Original"

Build:
```
git clone https://github.com/NicolasChoukroun/Franc
---------------------------
Unix: 
chmod -R 777 Franc
cd Franc
./maker.sh unix install
./maker.sh unix all
# then you can compile doing only
./maker.sh unix

-------------------------
Windows (using windows ubuntu subsystem):
chmod -R 777 Franc
cd Franc
./maker.sh win64 install
./maker.sh win64 all
# then you can compile doing only
./maker.sh win64

-------------------------
MAC:
chmod -R 777 Franc
cd Franc
./maker.sh osx install
./maker.sh osx all
# then you can compile doing only
./maker.sh osx

-------------------------
Deploy
./maker.sh win64 deploy
or
./maker.sh osx deploy
```

Generate keys:
```
PRIVATE_KEY="privatekey.txt"
PUBLIC_KEY="publickey.txt"
franc_PRIVATE_KEY="francprivatekey.txt"
franc_PUBLIC_KEY="francpublickey.txt"
echo "Generating private key"
openssl ecparam -genkey -name secp256k1 -rand /dev/urandom -out $PRIVATE_KEY
echo "Generating public key"
openssl ec -in $PRIVATE_KEY -pubout -out $PUBLIC_KEY
echo "Generating Franc private key"
openssl ec -in $PRIVATE_KEY -outform DER|tail -c +8|head -c 32|xxd -p -c 32 > $franc_PRIVATE_KEY
echo "Generating Franc public key"
openssl ec -in $PRIVATE_KEY -pubout -outform DER|tail -c 65|xxd -p -c 65 > $franc_PUBLIC_KEY
```


In call cases, the files are in the /binaries/ directory

## English - Franc: The crypto that gives and keeps on giving

from http://Franc.eu.com/whitepapers.php

₣ranc is designed to become both a good investment for the investors but also to become reserve currency for the ₣rance. 
We think that French state and its central bank should adopt this currency as a reserve currency along with Euro and Gold. Cryptocurrencies should be part of any portfolio and specifically be kept as a collateral by every country, not only ₣rance. China, and Russia are going to do their own Nationnal Cryptocurrency, ₣ranc should be the one ₣rance choose. Once the ₣ranc will be accepted as a reserve currency by the French state, it will be natural to print banknotes and coins, to be used for cash purchase. We do not think that all the cash should be repleased by digital transaction, but we rather see the future with ₣ranc ATM transactions, and total anonymity when using the ₣ranc banknotes and physical coins rather than storing these micro transactions into the blockchain. Le cash (banknote and coins) should survive to the digital age to guarantee immediate and anonymous des micro-transactions like for example buying a coffee with a 2 ₣ranc coin.

Bitcoin is the leading cryptocurrency with about 60% of all the crypto capitalization, the second one is far behind with 15% only. ₣ranc is based on the latest Bitcoin version and will follow all the new releases of Bitcoin in the future, thanks to ou Moulinette that can patch Bitcoin to make the ₣ranc in a quasi-automatic way. However, Bitcoin is crippled by some design issues that we have fixed in ₣ranc. but that the Bitcoin team cannot fix by respect to the original Bitcoin design. First Bitcoin will mine 21 Millions and then stop rewarding the miners. Like most others blockchain, they have all an end of life and this is not far away, 80% of the cryptocurrency will reach this existantial thread in the next 10 years. ₣ranc does not have this problem, it is the first cryptocurrency that has been designed to reward the miners forever, even in 10,000 years! ₣ranc also mine faster (every 2.5 minutes, where Bitcoin is mining every 5 minutes). Also the difficulty of ₣ranc is re-adjusted ever 20 minutes, which avoid predatory mining when a powerfull miner comes and get all the rewards for himself. Bitcoin is adjusting every two weeks, which is we think too slow. ₣ranc has many other small technical fixes that makes it a superior blockchain than Bitcoin on the paper. ₣ranc is designed like a tank, to last, millenium years if possible. Not many cryptocurrencies can say the same.

The ₣ranc is a true Blockchain, with its own certificates, own genesis, and started from scratch with its own parameters. It is designed to model the ₣ranc as it was when it was stopped. Our goal is to reach the following value: 0.15 Eur = 1 FRANC. We will issue 85 Billions of ₣rancs in the next 100 years which will match with the Gold reserve from the Bank of ₣rance. This way, the ₣ranc can become some sort of collateral reserve of wealth where the French people can save their money from the current finantial system and be sure that their money is protected by the inovative technology that is the blockchain trust system, that no one can change or modify. In one word, the ₣ranc is designed to be a financial Noah's Ark, that can resist to any financial storm, and that guarantee that the ₣rancs you own are saved, even in a total financial collapse event.

## French - Franc: La crypto qui donne et donne envie de donner

from http://Franc.com/whitepapers.php

₣ranc est conçu pour devenir à la fois un bon investissement pour les investisseurs mais également pour devenir une monnaie de réserve pour la ₣rance. 
Nous pensons que l'Etat français et sa banque centrale devraient adopter cette monnaie comme monnaie de réserve avec l'Euro et l'or. Les crypto-monnaies doivent faire partie de tout portefeuille et être spécifiquement conservées en garantie par tous les pays, pas seulement par la ₣rance. La Chine et la Russie vont créer leur propre crypto-monnaie nationale. ₣ranc devrait être la solution que la ₣rance choisira. Une fois que le ₣ranc sera accepté comme monnaie de réserve par l’État français, il sera naturel d’imprimer des billets de banque et des pièces de monnaie à utiliser pour un achat au comptant. Nous ne pensons pas que toutes les espèces devraient être remplacées par des transaction numérique, mais nous envisageons l'avenir avec les transactions ₣ranc ATM et l'anonymat total lors de l'utilisation des billets de banque et des pièces physiques ₣ranc plutôt que de stocker ces micro-transactions dans la chaîne de blocs. Le cash (billets de banque et pièces) devrait survivre jusqu'à l'ère numérique pour garantir des micro-transactions immédiates et anonymes, comme par exemple l'achat d'un café avec une pièce de 2 ₣ranc.

Bitcoin est la principale crypto-monnaie avec environ 60% de toute la capitalisation cryptographique, la seconde est loin derrière avec 15% seulement. Le ₣ranc est basé sur la dernière version de Bitcoin et suivra toutes les nouvelles versions de Bitcoin dans le futur, grâce à la Moulinette qui peut patcher Bitcoin pour fabriquer le ₣ranc de manière quasi automatique. Cependant, Bitcoin est paralysé par certains problèmes de conception que nous avons résolus dans le ₣ranc. mais que l'équipe Bitcoin ne peut pas résoudre par respect à la conception originale de Bitcoin. Tout d'abord, Bitcoin exploitera 21 millions de pieces, puis cessera de récompenser les mineurs. Comme la plupart des autres chaînes de blocs, elles ont toutes une fin de vie et, ce n'est pas loin dans le futur, 80% de la crypto-monnaie atteindra leur fin dans les 10 prochaines années. Le ₣ranc n'a pas ce problème, c'est la première crypto-monnaie conçue pour récompenser les mineurs pour toujours, même dans 10 000 ans! Le ₣ranc mine également plus rapidement (toutes les 2,5 minutes, où Bitcoin mine toutes les 5 minutes). De plus, la difficulté du ₣ranc est réajustée toutes les 20 minutes, ce qui évite les prédateurs lorsqu'un puissant mineur vient miner toute la récompense pour lui-même. Bitcoin s’adapte toutes les deux semaines, ce qui nous semble trop lent. ₣ranc a beaucoup d'autres petites corrections techniques qui en font une blockchain supérieure à Bitcoin sur le papier. ₣ranc est conçu comme un tank, pour durer, si possible des millénaires. Pas beaucoup de crypto-monnaies peuvent dire la même chose.

Le ₣ranc est une vraie blockchain, avec ses propres certificats, sa propre genèse, et est parti de zéro avec ses propres paramètres. Il est conçu pour modéliser le ₣ranc tel qu'il était quand il a été arrêté. Notre objectif est d’atteindre la valeur suivante: 0,15 Eur = 1 FRANC. Nous allons émettre 85 milliards de ₣rancs au cours des 100 prochaines années, ce qui correspondra à la réserve d'or de la Banque de ₣rance. De cette façon, le ₣ranc peut devenir une sorte de réserve collatérale de richesse où les Français peuvent économiser leur argent hors du système financier actuel et être sûr que leur argent est protégé par l'inovation technologique qu'est la blockchain, que personne ne peut changer ou modifier. En un mot, le ₣ranc est conçu pour être une arche de Noé financière, capable de résister à toute les tempêtes du système financier et garantissant que les ₣rancs que vous possédez sont sauvés, même en cas de crise financière totale.

## License
Franc Core is released under the terms of the MIT license. See COPYING for more information or see https://opensource.org/licenses/MIT.
