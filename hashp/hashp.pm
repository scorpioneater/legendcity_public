#hashp, the hash processor and hash|.

while (<STDIN>){  push(@lines,$_);}
@tokens;@funcSymbols = ('+','-','*','.+','&');
sub addition {  my ($x,$y) = @_;  return ($x+$y);}
sub subtraction {  my ($x,$y) = @_;  return ($x-$y);}
sub multiplication {  my ($x,$y) = @_;  return ($x*$y);}
sub concatenation {  my ($x,$y) = @_;  return (${x}.${y});}
%customFunctions = ();
sub newfunc {  my ($symbol) = shift;
print "Creating function for ${symbol}\n";
push(@funcSymbols,$symbol);  $customFunctions{$symbol} = @_;}

%functions = (  '+' => \&addition,  '-' => \&subtraction,  '*' => \&multiplication,  '.+' => \&concatenation,  '&' => \&newfunc);
my $sum = &{$functions{'+'}}(2,2);print "${sum}\n";
@containerTokens = ();
sub Container::new {  my $class = shift;   my $self = {      _name => shift,      _symbol  => shift,      _body => ()   };      my %body = ();   bless $self,$class;   return $self;};sub Container::toString {  my ($self) = @_;  my $name = $self->{_name};  my $symbol = $self->{_symbol};  my $ret = "name:${name} symbol:${symbol} ";  keys %{$self->{_body}};  while(my ($k,$v) = each %{$self->{_body}}){    $ret .= "key:${k} values:";    map {$ret .= "${_},"} @{$v};    $ret .= " ";  }  return $ret;};sub Container::addArgsToBody{   my ($self,$key,$arr) = @_;  $self->{_body}{$key} = $arr;};sub Container::get{  my ($self,$key) = @_;  return @{$self->{_body}{$key}};};
my $c = new Container("yyz","-");my @a = (23,75,97);$c->addArgsToBody(0,\@a);print "\n";print $c->toString();print "\n";
%containers = ();
$state = "INIT";
map {  map {body($_)} split (/ /,$_);}
@lines;
sub body() {  print "Current Token:${_} State:${state}\n";  
              if ($state eq "INIT"){    
                    if($_ eq '{'){ print "Found function def opening\n";} else {      if ($_ =~ /^[a-zA-Z]+\w+$/){         print "Found container name\n";         push (@tokens,$_);         $state = "BEGIN_CONTAINER";      } else {        if($_ =~ /^\w+\(.*\)/){           print "Found container element\n";           $state = "BEGIN_CONTAINER_ELEMENT";           parseContainerElement($_);           $state = "INIT";        }      }    }  }elsif ($state eq "BEGIN_CONTAINER") {    if ($_ ~~ @funcSymbols) {      print "Found defined function symbol\n";      push (@tokens,$_);      $state = "FOUND_SYMBOL";    } else {      print "PARSE ERROR: expected function symbol, \"${_}\" is undefined\n";      exit 1;    }  }elsif ($state eq "FOUND_SYMBOL") {    if ($_ =~ /^\[/) {      if ($_ !~ /\]/) {      print "Found container opening bracket\n";      $state = "FOUND_CONTAINER_START";      push (@containerTokens,$_);      }    }  } elsif ($state eq "FOUND_CONTAINER_START") {    if ($_ !~ m/\]/) {      print "Ending bracket not found, pushing on stack\n";      push (@containerTokens,$_);    } else {      print "Found container closing bracket\n";      if ($_ !~ m/\]$/) {        print "PARSE_ERROR: Symbols found after closing bracket, space expected\n";        exit 1;      }            $state = "FOUND_CONTAINER_END";      push (@containerTokens,$_);      if(parseContainer()){        #$state = "CREATED_CONTAINER";        $state = "INIT";      } else {        print "PARSE_ERROR: Error creating container/n";        exit 1;      }    }  } elsif ($state eq "CREATED_CONTAINER"){    if($_ =~ /^\w+\(.*\)/){      print "Found container element\n";      parseContainerElement($_);      $state= "INIT";    }  } elsif ($state eq "BEGIN_CONTAINER_ELEMENT"){      }}
sub parseContainer {  my $containerBody = join (' ', @containerTokens);  print "Parsing container body ${containerBody}\n";  #$containerBody =~ s/^.*\(//;  #$containerBody =~ s/\).*//;  $containerBody =~ s/\[//;  $containerBody =~ s/\]//;  print $containerBody."\n";  #chomp($containerBody);  #$containerBody = removeBrackets($containerBody);  #     substr ($containerBody,1,length($containerBody)-2);   #print $containerBody."\n";    my @containerElements = split (/,/,$containerBody);  print @tokens;  print "\n";    my $symbol = pop @tokens;  my $name = pop @tokens;  print "name:${name} symbol:${symbol}\n";    my $c = new Container($name,$symbol);
  my $i=0;  map {parseElement($_,$i++,$c)} @containerElements;  $containers{$name} = $c;  print $containers{$name}->toString();  print "\n";  @containerTokens = ();  return true;}
sub parseElement {  my $i= $_[1];  my $cont= $_[2];  #print "${i}\n";  $_ =~ s/^\s+//;  $_ =~ s/\s+$//;  my $key = "";  if ($_ =~ /^\w+\:/){    $key = substr $_,0,rindex($_,":");    #print "Found key: ${key}\n";    $_ = substr $_,rindex($_,":")+1;    #print "${_}\n";  }  my @arguments;  map {push (@arguments,$_);}        split (/ /,$_);  map{print "${_},"} @arguments;  print "\n";  $cont->addArgsToBody($i,\@arguments);  $cont->addArgsToBody($key,\@arguments);  print "arguments at ${i}\n";  map {print "${_},"} $cont->get($i);  print "\n";  if ($key ne "") {     print "arguments at ${key}\n";     map {print "${_},"} $cont->get($key);     print "\n";  }}
sub parseContainerElement{  $_ =~ s/^\s+//;  $_ =~ s/\s+$//;    my $baseName = substr $_,0,rindex($_,"(");  print "Found base container name: ${baseName}\n";  if (exists $containers{$baseName}) {    print "Found container for ${baseName}\n";    my $parameters = extractContainerElementParameters($_);    print "${parameters}\n";    print parseContainerElementParameters($parameters,$containers{$baseName});    print "\n";  } else {    print "PARSE_ERROR: ${baseName} has not been defined\n";    exit 1;  }}
sub extractContainerElementParameters {  my $ret = $_;  $ret =~ s/^.*\(//;  $ret =~ s/\).*//;  return $ret;}
sub parseContainerElementParameters {  my ($parameters,$c) = @_;  my @ar = $c->get($parameters);  if(@ar <= 0) {    print "PARSE_ERROR: container name not found for parameter\n";    exit 1;  }    print $c->{_symbol}."\n";    if($c->{_symbol} eq '&') {    print "funky\n";    &{$functions{$c->{_symbol}}}(@ar);  } else {  my $n = shift @ar;    map {    $n = &{$functions{$c->{_symbol}}}($n,$_);  } @ar;  return $n;  }}#body + [a:1 2,b:5 6 8]#main . [body()]#main()
#{ myfunc (arg1,arg2,arg3;)[#x + [arg1 arg2 arg3]#y * [x() 2]#y()#]}
#operators#+ add#- subtract#* multiply#/ divide#% mod#^ power#~ match#! negate#. void#| bitwise or
