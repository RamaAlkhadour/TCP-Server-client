use warnings; use strict;

$| = 1; # Autoflush

use IO::Socket;
use IO::Select;

my $socket = IO::Socket::INET->new(
                 PeerAddr    => 'localhost',
                 PeerPort    =>  1024,
                 Proto       => 'tcp',
                 Timeout     =>  1
             )
             or die "Could not connect";


my $select = IO::Select->new();

$select -> add (\*STDIN);
$select -> add ($socket);

while (1) {
  print "write message to send";
  print "$!\n";
  while (my @ready = $select -> can_read) {
	
    foreach my $fh (@ready) {
       if ($fh == $socket) {
          my $buf = <$socket>;
print "From Server   :";
          print $buf;
       }
       else {

		
         my $buf = <STDIN>;
         print $socket $buf

       }
    }
  }
  print "$!\n";
}
