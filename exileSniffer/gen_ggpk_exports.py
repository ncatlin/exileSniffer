import murmur2

import json, os

from operator import itemgetter

import PyPoE
from PyPoE.poe.file import dat
from PyPoE.poe.file.specification import load
from PyPoE.poe.file.ggpk import GGPKFile

'''
This requires the PyPoE library to be installed and working

https://github.com/OmegaK2/PyPoE

Put the path of your POE directory below.
You may want to specify a location for the resulting ggpk_exports.json too.
'''
poedir = "C:\\Program Files\\Grinding Gear Games\\Path of Exile\\"
targetFile = "ggpk_exports.json"






def createggpkfile(poe_path):
    ggpk = GGPKFile()
    ggpk.read(os.path.join(poe_path, 'content.ggpk'))
    ggpk.directory_build()

    return ggpk

def getDatIterator(ggpkobj, datname):
 
    df = dat.DatFile(datname)
    try:
        node = ggpkobj['Data/' + datname]
    except FileNotFoundError:
        return

    opt = {'use_dat_value': False, }
    reader = df.read(node.record.extract(), **opt)
    rit = reader.row_iter()
    return rit

'''
codes for each game area, used by the client for
the loading splash screen and loading the area itself
'''
def load_world_areacodes(ggpkobj):
    print("Loading world areacodes")
    resultDict = {}
    
    rit = getDatIterator(ggpkobj, "WorldAreas.dat")
    for i in rit:
        resultDict[i['Unknown6']] = i['Name']

    return resultDict

def load_monster_varieties(ggpkobj):
    print("Loading monster varieties")

    resultDict = {}
    
    rIt = getDatIterator(ggpkobj, "MonsterVarieties.dat")
    for i in rIt:
        istring = i['Id']
        objhash = murmur2.murmur2_32(istring.encode('ascii'), 0)
        resultDict[objhash] = istring

    return resultDict

def load_monster_varieties_index(ggpkobj):
    print("Loading monster variety indexes")
    resultList = []
    
    rIt = getDatIterator(ggpkobj, "MonsterVarieties.dat")
    for i in rIt:
        resultList.append(i['Id'])
    return resultList

def load_chests(ggpkobj):
    print("Loading chests")
    resultDict = {}
    
    rit = getDatIterator(ggpkobj, "Chests.dat")

    for i in rit:
        objhash = murmur2.murmur2_32(i['Id'].encode('ascii'), 0)
        resultDict[objhash] = i['Id']

    return resultDict

def load_characters(ggpkobj):
    print("Loading characters")
    resultDict = {}
    
    rit = getDatIterator(ggpkobj, "Characters.dat")

    for i in rit:
        objhash = murmur2.murmur2_32(i['Id'].encode('ascii'), 0)
        resultDict[objhash] = i['Id']

    return resultDict

def load_npcs(ggpkobj):
    print("Loading npcs")
    resultDict = {}
    
    rit = getDatIterator(ggpkobj, "NPCs.dat")

    for i in rit:
        objhash = murmur2.murmur2_32(i['Id'].encode('ascii'), 0)
        resultDict[objhash] = i['Id']

    return resultDict

def load_pets(ggpkobj):
    print("Loading pets")
    resultDict = {}
    
    rit = getDatIterator(ggpkobj, "Pet.dat")

    for i in rit:
        objhash = murmur2.murmur2_32(i['Id'].encode('ascii'), 0)
        resultDict[objhash] = i['Id']

    return resultDict

def load_items(ggpkobj):
    print("Loading items")
    resultDict = {}

    try:
        rit = getDatIterator(ggpkobj, "BaseItemTypes.dat")
    except:
        print("Failed to load baseItemTypes.dat")
        return resultDict

    for i in rit:
        objhash = murmur2.murmur2_32(i['Id'].encode('ascii'), 0)
        resultDict[objhash] = i['Id']

    return resultDict

def load_item_visuals(ggpkobj):
    print("Loading item visual identities")
    resultDict = {}

    rit = getDatIterator(ggpkobj, "ItemVisualIdentity.dat")
    for i in rit:
        ref = int(i['UnknownUniqueInt'])
        resultDict[ref] = i['Id']
    return resultDict

def load_item_effects(ggpkobj):
    print("Loading item visual effects")
    resultDict = {}

    rit = getDatIterator(ggpkobj, "ItemVisualEffect.dat")
    for i in rit:
        ref = int(i['Unknown0'])
        resultDict[ref] = i['Id']
    return resultDict 

def load_stats(ggpkobj):
    print("Loading stats")
    resultList = []
    
    rit = getDatIterator(ggpkobj, "Stats.dat")

    for rowindex, i in enumerate(rit):
        resultList.append(i['Id'])

    return resultList

def load_buf_visuals(ggpkobj):
    print("Loading buff visuals")
    resultList = []
    
    rit = getDatIterator(ggpkobj, "BuffVisuals.dat")

    for rowindex, i in enumerate(rit):
        resultList.append(i['Id'])

    return resultList

def load_buf_defs(ggpkobj):
    print("Loading buff definitions")
    resultList = []
    recoveryBuffs = []
    
    rit = getDatIterator(ggpkobj, "BuffDefinitions.dat")

    for rowindex, i in enumerate(rit):
        resultList.append([i['Id'], len(i['StatsKeys'])])
        if (i['IsRecovery'] == True):
            recoveryBuffs.append(rowindex)

    return resultList, recoveryBuffs


def load_objregister(ggpkfile):
    print("Loading object register")
    rnode = ggpkfile["Metadata/GameObjectRegister"]
    filebytes = rnode.record.extract()
    filebytes.seek(2)

    hashes = {}

    linelen = -1
    while linelen:
        ln = filebytes.readline()
        linelen = len(ln)
        
        if linelen < 1:
            break

        # handle issues from first and last lines
        if linelen%2 != 0:            
            if (ln[0] == 0):
                ln = ln[1:]
            else:
                ln = ln[:-1]
                
            objstring = ln.decode("utf-16-le").strip()
        else:
            objstring = ln.decode("utf-16-be").strip()

        ascbytes = objstring.encode('ascii')
        objhash = murmur2.murmur2_32(ascbytes, 0)
        hashes[objhash] = objstring
        
    return hashes

def load_prophecies(ggpkobj):
    print("Loading prophecies")
    result = {}

    rit = getDatIterator(ggpkobj, "Prophecies.dat")

    for i in rit:
        reference = int(i['UnknownUnique'])
        result[reference] = i['Id']

    return result
    
def load_hideouts(ggpkobj):
    print("Loading hideouts")
    result = {}

    rit = getDatIterator(ggpkobj, "Hideouts.dat")

    for i in rit:
        reference = int(i['Unknown0'])
        result[reference] = i['Id']

    return result
    
    

def savefile(resultdict, targetfilename):
    
    resultjson = json.dumps(resultdict)

    testfd = open(targetfilename, 'w')
    testfd.write(resultjson)
    testfd.close()


def getItemHashes():
    fd = open("C:\\Users\\nia\\Documents\\Visual Studio 2017\\Projects\\exileSniffer\\exileSniffer\\itemhashes.json")
    js = json.load(fd)
    itemhashes = js['ItemHashes']
    fd.close()
    return itemhashes
    

if __name__ == "__main__":

    st = "Metadata/Monsters/Spiders/SpiderExplodeFastWithExperience2"
    st = "Metadata/Monsters/Skeletons/SkeletonFireLightning"
    
    st = "Metadata/Monsters/Spiders/SpiderThornExplodeMinionsOnDeath2" #0x7fe07acf
    st = "OneHandMace8"
    #st = "Metadata/Monsters/LeagueBestiary/SpiderPlatedBestiarySpiritBoss" #0xc0a52243
    #st = "Metadata/Monsters/Scorpion/Scorpion"
    st = "Metadata/Pet/BabyElephant/BabyElephant"
    ascbytes = st.encode('ascii')
    print(hex(murmur2.murmur2_32(ascbytes, 0)))
    st = "HideoutBeach" 
    #exit()

    print("Loading GGPK")
    ggpkobj = createggpkfile(poedir)

    print("Gathering data...")
    resultdict = {}
    resultdict['MonsterVarietiesHashes'] = load_monster_varieties(ggpkobj)
    resultdict['MonsterVarietiesIndex'] = load_monster_varieties_index(ggpkobj)
    resultdict['AreaCodes'] = load_world_areacodes(ggpkobj)
    resultdict['ObjRegisterHashes'] = load_objregister(ggpkobj)
    resultdict['ChestHashes'] = load_chests(ggpkobj)
    resultdict['CharacterHashes'] = load_characters(ggpkobj)
    resultdict['NPCHashes'] = load_npcs(ggpkobj)
    resultdict['PetHashes'] = load_pets(ggpkobj)
    resultdict['ItemHashes'] = getItemHashes()#load_items(ggpkobj)
    resultdict['ItemVisuals'] = load_item_visuals(ggpkobj)
    resultdict['ItemVisualEffects'] = load_item_effects(ggpkobj)
    resultdict['StatIndexes'] = load_stats(ggpkobj)
    resultdict['BuffDefinitions'], resultdict['RecoveryBuffs'] = load_buf_defs(ggpkobj)
    resultdict['BuffVisuals'] = load_buf_visuals(ggpkobj)
    resultdict['Prophecies'] = load_prophecies(ggpkobj)
    resultdict['Hideouts'] = load_hideouts(ggpkobj)
    
    

    savefile(resultdict, targetFile)
    print("Done")
    

