#!/usr/bin/perl

use strict;

sub generateSpringShit{
    my $inputString = shift(@_); 
    my ($methods,$datastructure) = parseElements(split(/\|/,$inputString));
	my $code = generateBoilerPlate();
	print "Parsed the following elements from input string :\n";
	print "Methods :\n";
	map {print "\t${_}\n";} @{$methods};
	print "Datastructure :\n";
	map {print "\t${_}\n";} @{$datastructure};
	my $boilerPlate = generateBoilerPlate();
	my $methodTemplate = generateMethodTemplate()."\n";
	my $dataStructureTemplate = generateDatastructureTemplate()."\n";
	generateMethods($methodTemplate,@{$methods});
	#generateDataStructure($dataStructureTemplate,$datastructure);
    
}

sub parseElements{
	my @methods;
	my @datastructure;
    map { 
    	my $element = $_; $element =~ s/:.*//g;
    	my $dataString = $_; $dataString =~ s/^.*://g;
    	my @items = split(/,/,$dataString);	
		push(@methods,@items) if($element eq "methods");
		push(@datastructure,@items) if($element eq "datastructure");
    } @_;
	
	return \@methods, \@datastructure;
}

sub generateBoilerPlate {
	open(my $fh, "<", "hackerdoucheboilerplate.java") or die "Can't open < hackerdoucheboilerplate.java: $!";
    my $output;
    while (my $line = readline($fh)) {$output.=$line;}
	close($fh);
	return $output;
}

sub generateMethodTemplate {
	 my $methodString = shift(@_);
	 my $javashit = "\t\t\@GetMapping(produces = \"application/json\")\n\t\t\tEntry <--METHOD-->(<--PARAMS-->){\n\t\t\t\treturn find<--METHOD-->(<--ARGS-->);\n\t\t\t}\n\n\t\t\tEntry find<--METHOD-->(<--PARAMS-->) {\n\n\t\t\tEntry entry = new Entry();\n\n\t\t\t\treturn new Entry();\n\t\t\t}";
	 return $javashit;
}

sub generateDatastructureTemplate {
	my $datastructureString = shift(@_);
	my $javashit = "class Entry {\n\tprivate String barcode;\n\tprivate String item;\n\tprivate String category;\n\tprivate Integer price;\n\tprivate Integer discount;\n\tprivate Integer available;\n\t}\n}";
	return $javashit;
}

sub generateMethods {
	my $methodTemplate = shift(@_);
	my @methods = @_;
	#print $methodTemplate."\n";
	#print @methods;
	
	map {
		my $methodDefinition = $methodTemplate;
		my ($methodName,$methodParams) = parseMethods($_);
		my $params = generateParams($methodParams);
		$methodDefinition =~ s/\<\-\-METHOD\-\-\>/${methodName}/g;
		$methodDefinition =~ s/\<\-\-PARAMS\-\-\>/${params}/g;
		my $args = generateArgs($methodParams);
		$methodDefinition =~ s/\<\-\-ARGS\-\-\>/${args}/g;
		print "$methodDefinition\n";
	} @methods;	
}

sub parseMethods {
	#getFilteredEntryById-i_initialRange&i_finalRange
	my $methodString = shift(@_);
	my $methodName = $methodString;
	my $methodParams = $methodString;
	$methodName =~ s/-.*$//g;
	$methodParams =~ s/^.*-//g;
	#print "Result of parsing  :\n";
	#print $methodName."\n";
	#print $methodParams."\n";	
	
	return $methodName,$methodParams;
}

sub generateParams {
	my $params = shift(@_);
	my @paramArr = split(/&/,$params);
	my $output;
	map {
	my $param = $_;
	$output .= "\@PathVariable int " if ($param = m/i/);
	$output .= "\@PathVariable String " if ($param = m/s/);
	$param =~ s/^.*\_//g;
	$output .= "${param},";
	} @paramArr;
	
	return $output;
}

sub generateArgs {
	my $args = shift(@_);
	my @args = split(/&/,$args);
	my $output;
	map {
	my $args = $_;
	$args =~ s/^.*\_//g;
	$output .= "${args},";
	} @args;
	
	return $output;
}

sub generateDataStructure {
	my ($dataStructureTemplate,@dataStructure) = shift @_;
	print $dataStructureTemplate."\n";
	map {print "\t${_}\n";} @dataStructure;
}

sub parseDataStructure {
	#s_barcode
	my $dataStructureString = shift(@_);
}

generateSpringShit($ARGV[0]);
