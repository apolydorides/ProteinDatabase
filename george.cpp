class Protein {
    id;
    gid;
    name;
}

class Proteins {
    private:
    vector<Protein> prots;

    public:
    add_protein(Protein p){
        prots.push_back(p);
    }

    find_name(string name) {
        for(Protein prot : prots){
            if(prot.name == name) {
                return prot
            }
        }   
    }
}



void () {
    Proteins ps;
    int id = 0;
    //open file
    // while not end of file
        ps.add_protein(Protein(id,gid,name,sequence));
        id++;
    // end loading

    
}