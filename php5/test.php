<?PHP
include ("ITVC.php");

$msg = "A Quick Brown Fox Jumps Over The Lazy Dog.";

$len = 122 - 33;

$src = new ITV_Characters(33, 33, $len);
$len += $src->load(32, 32, 1);

$src_cs = $src->shuffle();
$key = $src->dump_table();

echo "Key: " . $key . "\nChecksum: " . $src_cs . "\n";

$enc = $src->encode($msg);

echo "Encrypted: " . $enc . "\n";

$src = NULL;

$dst = new ITV_Characters($key);
$key = $dst->dump_table();
$dst_cs = $dst->checksum();

if ($src_cs == $dst_cs) {
	echo "Checksum OK: " . $dst_cs . "\n";
};

$dec = $dst->decode($enc);

echo "Decrypted: " . $dec . "\n";

?>
