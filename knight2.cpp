#include "knight2.h"

/* * * BEGIN class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

bool Pytagores(int hp) {
    if(hp<100) return false;
    else{
        int a,b,c;
        a=hp%10;
        hp/=10;
        b=hp%10;
        hp/=10;
        c=hp;
        if(a==0 ||b==0||c==0)
            return false;
        if(a*a+b*b==c*c || b*b+c*c==a*a || a*a+c*c==b*b)
            return true;
        return false;
    }
}

bool Prime(int hp){
    int uoc=0;
    for(int i=1;i<=hp;i++){
        if(hp%i==0)
            uoc++;
    }
    if (uoc==2) return true;
        return false;
}


BaseKnight * BaseKnight:: create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
     BaseKnight * hiepsi= new BaseKnight; 
        hiepsi->id=id;
        hiepsi->maxhp=maxhp;
        hiepsi->level=level;
        hiepsi->gil=gil;
        hiepsi->antidote=antidote;
        hiepsi->phoenixdownI=phoenixdownI;
        hiepsi->hp=maxhp;
        
        //cap KnightType cho hiepsi
        if(Pytagores(maxhp)) hiepsi->knightType=DRAGON;
        else if(Prime(maxhp)) hiepsi->knightType=PALADIN;
        else if(maxhp==888) hiepsi->knightType=LANCELOT;
        else hiepsi->knightType=NORMAL;
        hiepsi->bag= new BaseBag(hiepsi,phoenixdownI,antidote);
        
        return hiepsi;
}

    //show
KnightType BaseKnight:: showKnight() {return this->knightType;};
int BaseKnight:: showPhoenixI(){return this->phoenixdownI;};
int BaseKnight:: showAnti(){return this->antidote;};
int BaseKnight:: showLevel(){return this->level;};
int BaseKnight:: showHP(){return this->hp;};
int BaseKnight:: showMaxhp(){return this->maxhp;};
int BaseKnight:: showGil(){return this->gil;};
BaseBag* BaseKnight:: showBag(){return this->bag;};
bool BaseKnight:: showCursed(){return this->Cursed;};
    
    // //Update
void BaseKnight:: updateAntidote(int new_anti){this->antidote=new_anti;};
void BaseKnight:: updatePhoenixDown(int new_phoenix){this->phoenixdownI=new_phoenix;};
void BaseKnight:: updateHP(int new_hp){this->hp=new_hp;};
void BaseKnight:: updateGil(int new_gil){this->gil=new_gil;};
void BaseKnight:: updateCursed(bool s){this->Cursed=s;};
void BaseKnight:: updateLevel(int l){this->level=l;};

/* * * END class BaseKnight * * */


/* * BEGIN class Item * */
bool PhoenixdownI::canUse(BaseKnight * knight) {
    if(knight->showHP()<=0 && knight->decreased)
        return true;
    else return false;
}

void PhoenixdownI::use(BaseKnight * knight) {
    knight->updateHP(knight->showMaxhp());
    
    knight->decreased=false;
}

bool PhoenixdownII::canUse(BaseKnight * knight) {
    if(knight->showHP()<(int)knight->showMaxhp()/4 && knight->decreased)
        return true;
    else return false;
}

void PhoenixdownII::use(BaseKnight * knight) {
    knight->updateHP(knight->showMaxhp());
    knight->decreased=false;
}

bool PhoenixdownIII::canUse(BaseKnight * knight) {
    if(knight->showHP()<(int) knight->showMaxhp()/3 && knight->decreased)
        return true;
    else return false;
}

void PhoenixdownIII::use(BaseKnight * knight) {
    if(knight->showHP()<=0)
       { knight->updateHP((int)knight->showMaxhp()/3);}
    else {knight->updateHP(knight->showHP()+(int)knight->showMaxhp()/4);}
    knight->decreased=false;
}

bool PhoenixdownIV::canUse(BaseKnight * knight) {
    if(knight->showHP()<(int) knight->showMaxhp()/2 && knight->decreased)
        return true;
    else return false;
}

void PhoenixdownIV::use(BaseKnight * knight) {
    if(knight->showHP()<=0)
        {knight->updateHP((int)knight->showMaxhp()/2);}
    else {knight->updateHP(knight->showHP()+(int)knight->showMaxhp()/5);}
    knight->decreased=false;
}

bool Anti_dote::canUse(BaseKnight * knight) {
    if (knight->showCursed()) return true;
    else return false;
}                       

void Anti_dote::use(BaseKnight * knight) {
    knight->updateCursed(false);
}

/* * END class Item * */


/* BEGIN class BaseOpponent */
void BaseOpponent::fighting(BaseKnight * fightedK){
    //cout<<this->level0<<endl;
    if(fightedK->showLevel()>=this->level0 || fightedK->showKnight()==PALADIN || fightedK->showKnight()==LANCELOT){  //level0 cho quai vat se duoc tinh sau trong adventure cua Armyknight//
        //cout<<1<<endl;
        fightedK->updateGil(fightedK->showGil()+this->gil);
    }
    else {
        //cout<<1<<endl;
        fightedK->updateHP(fightedK->showHP()-basedamage*(level0-fightedK->showLevel()));
        fightedK->decreased=true;
        }
    };

/* END class BaseOpponent */


/* BEGIN class BaseBag */

BaseItem * BaseBag::get (ItemType itemType) { //tu tu doi chut //ok cha khac j :>
    BaseItem * timkiem= this->head;
    for(int i=0;i<this->currentItem;i++){
        if(timkiem->loaiItem==itemType){         
            return timkiem;
        }
        else timkiem=timkiem->next;
    }
    return NULL;
}

BaseItem * BaseBag:: Search(BaseKnight* s) {
    BaseItem * timkiem= this->head;
    for(int i=0;i<this->currentItem;i++){
        if(timkiem->canUse(s)){         
            return timkiem;
        }
        else timkiem=timkiem->next;
    }
    return NULL;
}

void BaseBag:: SwapHead(BaseItem * founditem) {
    BaseItem* pX=head;
    BaseItem* pY=head;
    BaseItem* prev=NULL;
    while(pY!=NULL && pY->loaiItem!=founditem->loaiItem){
        prev=pY;
        pY=pY->next;
    }
    BaseItem* temp=pY->next;
    if(pX->next!=pY){
    pY->next=pX->next;
    pX->next=temp;
    head=pY;
    prev->next=pX;
    }
    else{
        pY->next=pX;
        pX->next=temp;
        head=pY;
    }
}

void BaseBag:: DeleteHead() {
    BaseItem* tem=head;
    head=head->next;
    tem->next=nullptr;
    this->currentItem--;
    if(this->head->loaiItem==Antidote) this->belongtoK->updateAntidote(this->belongtoK->showAnti()+1);
    if(this->head->loaiItem==PhoenixI) this->belongtoK->updatePhoenixDown(this->belongtoK->showPhoenixI()+1);
    delete tem;
} 

string BaseBag:: toString() const {
    string tenitem[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    string toPrint="Bag[count=";
    toPrint+=to_string(this->currentItem);//currentItem la num ha? ua
    BaseItem* ptr=this->head;  //may cai nay dung k? hmm thay van duoc

    for(int i=0;i<this->currentItem;i++){
        toPrint+=";"; 
        toPrint+=tenitem[ptr->loaiItem];
        ptr=ptr->next;
    }
    toPrint+="]"; 
    return toPrint;
}

/* END class BaseBag */



/* * * BEGIN class ArmyKnights * * */

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

//printResult(armyKnights->adventure())
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string & file_armyknights) {
    ifstream info (file_armyknights);
    if(info.fail()){
            cout<<"Khong mo duoc file_armyknights";
            terminate();
    }
    info>>armynum;
    int HP,level,phoen,gil,anti;
    
    Armygroup=new BaseKnight*[armynum];
    for(int i=0;i<armynum;i++){
            info>>HP>>level>>phoen>>gil>>anti;
            Armygroup[i]=Armygroup[i]->create(i+1,HP,level,gil,anti,phoen);
    }
}

ArmyKnights::~ArmyKnights() {
    delete[] Armygroup;
    Armygroup=nullptr;
}

int ArmyKnights::count() const{
    return armynum;
}

BaseKnight * ArmyKnights::lastKnight() const{
    if(armynum<=0) return NULL;
    else return Armygroup[armynum-1];
}

void ArmyKnights:: passThing(BaseItem* vatpham){
    int u=this->armynum-2;
    while(!Armygroup[u]->bag->insertFirst(vatpham)){
        u--;
    }
    if(u>=0) Armygroup[u]->bag->insert(vatpham);
}

void ArmyKnights:: passGil() {
    int o=this->armynum-1;
    while(o>=0 && Armygroup[o]->showGil()>999){
        int passValue=Armygroup[o]->showGil()-999;
        Armygroup[o]->updateGil(999);
        if(o>0) Armygroup[o-1]->updateGil(Armygroup[o-1]->showGil()+passValue);
        o--;
    }
}

bool ArmyKnights::fight(BaseOpponent * doithu) {      /////chua xong nha
    //cout<<lastKnight()<<endl;
    doithu->fighting(this->lastKnight());
    if(doithu->isHades && this->lastKnight()->showHP()!=0) this->winHades=true;
    if(this->lastKnight()->showGil()>999){
        this->passGil();
    }
    if(this->lastKnight()->showHP()>999) this->lastKnight()->updateHP(999);
    if(this->lastKnight()->decreased || this->lastKnight()->showCursed()){  
        BaseItem* timthuoc=this->lastKnight()->bag->Search(this->lastKnight());
        if(timthuoc!=NULL){
            this->lastKnight()->bag->SwapHead(timthuoc);
            timthuoc->use(this->lastKnight());
            this->lastKnight()->bag->DeleteHead();
            this->lastKnight()->decreased=false;
        }
    }
    

    if(this->lastKnight()->showHP()<=0){  //goi phuong hoang
        if(this->lastKnight()->showGil()>=100){
            this->lastKnight()->updateGil((int)this->lastKnight()->showGil()-100);
            this->lastKnight()->updateHP((int)this->lastKnight()->showMaxhp()/2);
            this->lastKnight()->decreased=false;
        }
        else return false;
        
        if(this->lastKnight()->showHP()<=0) return false;
    
    }
    if(this->lastKnight()->showCursed()){
        int i=0;
        while(i<3 && this->lastKnight()->bag->head!=NULL){
            this->lastKnight()->bag->DeleteHead();          //lam roi 3 vat pham gan nhat
            i++;
        }
        this->lastKnight()->updateHP(this->lastKnight()->showHP()-10);
        this->lastKnight()->updateCursed(false);
        this->lastKnight()->decreased=true;
        
        BaseItem* dungthuoc=this->lastKnight()->bag->Search(this->lastKnight());
        if(dungthuoc!=NULL){
            this->lastKnight()->bag->SwapHead(dungthuoc);
            dungthuoc->use(this->lastKnight());
            this->lastKnight()->bag->DeleteHead();
            this->lastKnight()->decreased=false;
        }
        if(this->lastKnight()->showHP()<=0){
            if(this->lastKnight()->showGil()>=100){
            this->lastKnight()->updateGil((int)this->lastKnight()->showGil()-100);
            this->lastKnight()->updateHP((int)this->lastKnight()->showMaxhp()/2);
            this->lastKnight()->decreased=false;
            }
            else return false;
        
            if(this->lastKnight()->showHP()<=0) return false;
        }
        return true;
    }
    else return true;
}


bool ArmyKnights::adventure(Events * events) {
    for(int i=0;i<events->count();i++){
        int gett=events->get(i);
        int lv0=(i+gett)%10+1;
        //cout<<gett<<endl;
        switch(gett){
            case 1:{
            BaseOpponent* madbear= new MadBear(lv0);
            if(this->fight(madbear)){
            //cout<<1<<endl;
                this->printInfo();}
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete madbear;
            break;}
            
            ///////////////////////////////////////////////////////
            
            case 2:{
            BaseOpponent* bandit= new Bandit(lv0);
            if(this->fight(bandit))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete bandit;
            break;}
            
            /////////////////////////////////////////////////////
            
            case 3:{
            BaseOpponent* lord= new LordLupin(lv0);
            if(this->fight(lord))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete lord;
            break;}
            
            //////////////////////////////////////////////
            
            case 4:{
            BaseOpponent* elf= new Elf(lv0);
            if(this->fight(elf))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete elf;
            break;}
            
            //////////////////////////////////////////////
            
            case 5:{
            BaseOpponent* troll= new Troll(lv0);
            if(this->fight(troll))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete troll;
            break;}
            
            /////////////////////////////////////////////
            
            case 6:{
            BaseOpponent* torn= new Tornbery(lv0);
            if(this->fight(torn))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete torn;
            break;}
            
            //////////////////////////////////////////////
            
            case 7:{
            BaseOpponent* queen= new Queen(lv0);
            if(this->fight(queen))
                this->printInfo();
            else { 
            this->printInfo();
            this->armynum--;
            if(armynum==0) return false;
            }
            delete queen;
            break;}
            
            ////////////////////////////////////////////////
            
            case 8:{
            BaseOpponent* nina= new Nina();
            if(this->fight(nina)) this->printInfo();
            delete nina;
            break;}
            case 9:{
            BaseOpponent* durian=new Durian();
            if(this->fight(durian)) this->printInfo();
            delete durian;
            break;}
            
            ///////////////////////////////////////////////
            
            case 10:{
            if(!this->meetOmega){
                BaseOpponent* omega= new OmegaW();
                if(this->fight(omega))
                    this->printInfo();
                else { 
                this->printInfo();
                this->armynum--;
                if(armynum==0) return false;
                }
                this->meetOmega=true;
                delete omega;
            }
            break;}
            
            ///////////////////////////////////////////////
            
            case 11:{
            if(!this->meetHades){
                BaseOpponent* hades=new Hades();
                if(this->fight(hades)){
                    if(this->winHades) this->shield=true;
                    this->printInfo();
                }
                else { 
                this->printInfo();
                this->armynum--;
                if(armynum==0) return false;
                }
                this->meetHades=true;
            }
            break;}
            
            ///////////////////////////////////////////nhat do
            case 112:{
                BaseItem* phoen2=new PhoenixdownII();
                if(this->lastKnight()->bag->insertFirst(phoen2)){
                    this->lastKnight()->bag->insert(phoen2);
                }
                else {passThing(phoen2);}
                delete phoen2;
                this->printInfo();
            break;}
            
            case 113:{
                BaseItem* phoen3=new PhoenixdownIII();
                if(this->lastKnight()->bag->insertFirst(phoen3)){
                    this->lastKnight()->bag->insert(phoen3);
                }
                else {passThing(phoen3);}
                delete phoen3;
                this->printInfo();
            break;}
            
            case 114:{
                BaseItem* phoen4=new PhoenixdownIV();
                if(this->lastKnight()->bag->insertFirst(phoen4)){
                    this->lastKnight()->bag->insert(phoen4);
                }
                else {passThing(phoen4);}
                delete phoen4;
                this->printInfo();
            break;}
            
            //////////////////////////////////////nhat bao vat
            
            case 95:{
                if(!this->shield) this->shield=true;
                this->printInfo();
            break;}
            
            case 96:{
                if(!this->spear) this->spear=true;
                this->printInfo();
            break;}
            
            case 97:{
                if(!this->hair) this->hair=true;
                this->printInfo();
            break;}
            
            case 98:{
                if(this->hair && this->shield && this->spear) this->sword=true;
                this->printInfo();
            break;}
            
            case 99:{
                if(this->sword) return true;
                else if (this->hair && this->spear && this->shield){
                    int UltimeciaHP=5000;
                    double damage[3]={0.06,0.05,0.075};
                    while(armynum>0){
                        if(this->lastKnight()->showKnight()!=NORMAL){
                            UltimeciaHP-=(int)this->lastKnight()->showHP()*this->lastKnight()->showLevel()*damage[this->lastKnight()->showKnight()];
                            if(UltimeciaHP>0){this->lastKnight()->updateHP(0); armynum--;}
                            else {this->printInfo(); return true;}
                        }
                        else{
                        if(this->armynum==1) this->printInfo(); 
                        this->armynum--;}
                    }
                    return false;
                }
                else{
                    this->armynum=0;
                    return false;    
                }
            break;}
        }
    }
    return false;
}

/* * * END ArmyKnights * * */




/* * * BEGIN class KnightAdventure * * */



/* * * END class KnightAdventure * * */