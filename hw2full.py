from sys import argv

def open_files(argv):
    try:
        codon_file = open(argv[1], "r")
        sars_file = open(argv[2], "r")
        return codon_file, sars_file
    except FileNotFoundError:
        print("File not found.")
        exit(1)

def codon_table(codon_file):
    codon_dict = {}
    for line in codon_file:
        parts = line.strip().split()
        if len(parts) == 0:
            continue
        codon_dict[parts[0].upper()] = parts[1].upper()
    return codon_dict

def read_sequence(sars_file, codon_dict):
    dna_sequence = ''.join(line.strip().upper() for line in sars_file if not line.startswith('>'))
    result = ""
    for i in range(0, len(dna_sequence), 3):
        codons = dna_sequence[i:i + 3]
        if codons in codon_dict:
            result += codon_dict[codons]
        else:
            result += '?'
    return result

def read_frames(dna_sequence):
    start_codons = ["ATG"]
    stop_codons = ["TAA", "TAG", "TGA"]
    frames = []
    start_positions = [i for i in range(len(dna_sequence) - 2) if dna_sequence[i:i + 3] == start_codons]
    for start in start_positions:
        frame = ""
        i = start
        while i < len(dna_sequence):
            codons = dna_sequence[i:i + 3]
            frame += codons
            i += 3
            if codons in stop_codons:
                frames.append(frame)
                break
        else:
            frames.append(frame)
    return frames

def translate_frames(reading_frames, codon_dict, placeholder=''):
    trans_frames = []
    for frame in reading_frames:
        translated_frame = ""
        for i in range(0, len(frame), 3):
            codons = frame[i:i + 3]
            if codons in codon_dict:
                translated_frame += codon_dict[codons]
            else:
                translated_frame += placeholder
        trans_frames.append(translated_frame)
    return trans_frames

def reverse_sequence(sars_file, codon_dict):
    sars_file.seek(0)
    dna_sequence = ''.join(line.strip().upper() for line in sars_file if not line.startswith('>'))
    translated_sequence = ""
    for letter in dna_sequence[::-1]:
        if letter == 'A':
            translated_sequence += 'T'
        elif letter == 'T':
            translated_sequence += 'A'
        elif letter == 'C':
            translated_sequence += 'G'
        elif letter == 'G':
            translated_sequence += 'C'
        else:
            translated_sequence += letter
    return translated_sequence

def reverse_reading_frames(translated_sequence, codon_dict):
    reverse_frames = read_frames(translated_sequence)
    translated_read_frames = translate_frames(reverse_frames, codon_dict)
    return translated_read_frames

def main():
    codon_file, sars_file = open_files(argv)
    codon_dict = codon_table(codon_file)
    dna_sequences = ''.join(line.strip().upper() for line in sars_file if not line.startswith('>'))
    translated_sequences = read_sequence(sars_file, codon_dict)
    reading_frames = read_frames(dna_sequences)
    for frame in reading_frames:
        if frame:
            print(frame)
    
    sars_file.seek(0)
    translated_sequence = reverse_sequence(sars_file, codon_dict)
    reverse_frames = read_frames(translated_sequence)
    reverse_trans_frames = reverse_reading_frames(translated_sequence, codon_dict)
    for frame in reverse_trans_frames:
        if frame: 
            print(frame)
    
    codon_file.close()
    sars_file.close()

if __name__ == "__main__":
    main()
