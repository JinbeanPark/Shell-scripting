#!/usr/bin/python
#Jinbean Park
#805330751

import sys, random, string
from optparse import OptionParser

class shuf:
        
    def readLines(self, filename):
        try:
            with open(filename) as f:
                inputLines = f.readlines()
            inputLines = [x.strip() for x in inputLines]
            return inputLines
        except:
            parser.error("File cannot be opened\n")

    def shuffleLines(self, lines, hC = None, rP = False):
        if hC == None:
            if rP:
                return random.choice(lines)
            else:
                random.shuffle(lines)
                return lines
        else:
            if rP:
                listRepeat = []
                for i in range(hC):
                    listRepeat.append(random.choice(lines))
                return listRepeat
            else:
                if len(lines) > hC:
                    return random.sample(lines, hC)
                else:
                    return  random.sample(lines, len(lines))

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE 
                or:%prog -i LO-HI [OPTION]... 
                Write a random permutation of the input lines to standard output.
                Read from standard input if the arguments are zero non-option arguments or a single non-option argument '-'"""
    
    parser = OptionParser(usage=usage_msg)

    parser.add_option("-i", "--input-range", action = "store", dest = "inputRange", default = None, type = "string", help = "treat each number LO through HI as an input line")
    parser.add_option("-n","--head-count", action = "store", dest = "headCount", default = None, help = "Output at most COUNT lines")
    parser.add_option("-r","--repeat", action = "store_true",dest = "Repeat", default = False, help = "output lines can be repeated")

    opt, args = parser.parse_args(sys.argv[1:])
    generator = shuf()

    if opt.inputRange != None:
        if len(args) != 0:
            parser.error("There is an argument {0} on input-range mode\n".format(args[0]))
        
        lowHighNum = opt.inputRange.split('-', 1)
        
        if len(lowHighNum) < 2:
            parser.error("Inappropriate input-range was typed\n")
        try:
            lowInx = int(lowHighNum[0])
        except:
            parser.error("The type of input-range is inappropriate\n")
        try:
            highInx = int(lowHighNum[1])
        except:
            parser.error("the Type of input-range is inappropriate\n")
        if lowInx  > highInx + 1:
            parser.error("Inappropriate intput-range was typed\n")
        outputLines = list(range(lowInx, highInx + 1))

    else:
        if len(args) >= 2:
            parser.error("There are more than two arguments\nExtra argument {0}\n".format(args[1]))
        elif len(args) == 0 or args[0] == '-':
            outputLines = sys.stdin.readlines()
        else:
            FileName = str(args[0])
            outputLines = generator.readLines(FileName)
                
    if opt.headCount != None:
        try:
            headCount = int(opt.headCount)
        except:
            parser.error("The type of head-count is inappropriate\n")
        if headCount < 0:
            parser.error("The number of head-count is negative")

    if opt.Repeat:
        if outputLines == None:
            parser.error("There are no lines\n")
        if opt.headCount == None:
            while (True):
                sys.stdout.write(str(generator.shuffleLines(outputLines, opt.headCount, opt.Repeat)) + "\n")
        else:
            outputList = generator.shuffleLines(outputLines, headCount, opt.Repeat)
            for line in outputList:
                sys.stdout.write(str(line) + "\n")

    else:
        if opt.headCount == None:
            outputList = generator.shuffleLines(outputLines, opt.headCount, opt.Repeat)
            for line in outputList:
                sys.stdout.write(str(line) + "\n")
        else:
            outputList = generator.shuffleLines(outputLines, headCount, opt.Repeat)
            for line in outputList:
                sys.stdout.write(str(line) + "\n")


if __name__ == "__main__":
    main()
