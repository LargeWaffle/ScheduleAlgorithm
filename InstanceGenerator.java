/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package instancegenerator;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author Olivier Grunder
 */
public class InstanceGenerator {

//    public static int NBR_APPRENANTS = 20;
//    public static int NBR_FORMATIONS_PAR_SEMAINE = 4; // max 10 demi-journées par apprenant

    public static int NBR_APPRENANTS = 8*4;
    public static int NBR_FORMATIONS_PAR_SEMAINE = 3;

    public static int DIMENSION_ZONE_GEOGRAPHIQUE = 200;

    public static int NBR_INTERFACES = (int) (NBR_APPRENANTS/4 * 1.2);
    public static int NBR_FORMATIONS = NBR_APPRENANTS * NBR_FORMATIONS_PAR_SEMAINE;

    public static String FILENAME = "instance-formations" + NBR_FORMATIONS + ".h";

    public static int NBR_COMPETENCES = 2;
    public static String NOMS_COMPETENCES[] = {
        "COMPETENCE_SIGNES",
        "COMPETENCE_CODAGE"};

    public static int NBR_CENTRES_FORMATION = 5;
    public static int NBR_SPECIALITES = NBR_CENTRES_FORMATION;
    public static String NOMS_SPECIALITES[] = {
        "SPECIALITE_MENUISERIE",
        "SPECIALITE_ELECTRICITE",
        "SPECIALITE_MECANIQUE",
        "SPECIALITE_INFORMATIQUE",
        "SPECIALITE_CUISINE"};

    public static String JOURS_SEMAINE[] = {
        "LUNDI",
        "MARDI",
        "MERCREDI",
        "JEUDI",
        "VENDREDI",
        "SAMEDI"};

    protected BufferedWriter textFileOutput;

    Random rand;

    public InstanceGenerator() {
        rand = new Random();
        try {
            textFileOutput = new BufferedWriter(new FileWriter(FILENAME));

            writeHeader();
            writeCompetencesInterfaces();
            writeSpecialiteInterfaces();
            writeCoord();
            writeFormation();
            writeMain();

            textFileOutput.close();
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    //
    //#define NBR_INTERFACES        10
    //#define NBR_APPRENANTS	       8
    //#define NBR_CENTRES_FORMATION  3
    //#define NBR_SPECIALITES        3
    //#define NBR_NODES 	       NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS
    //
    ///* code des compétence en langage des signes et en codage LPC */
    //#define COMPETENCE_SIGNES      0
    //#define COMPETENCE_CODAGE      1
    private void writeHeader() {
        try {
            textFileOutput.write("#define NBR_INTERFACES        " + NBR_INTERFACES + "\n");
            textFileOutput.write("#define NBR_APPRENANTS        " + NBR_APPRENANTS + "\n");
            textFileOutput.write("#define NBR_FORMATIONS        " + NBR_FORMATIONS + "\n");
            textFileOutput.write("#define NBR_CENTRES_FORMATION " + NBR_CENTRES_FORMATION + "\n");
            textFileOutput.write("#define NBR_SPECIALITES       " + NBR_SPECIALITES + "\n");
            textFileOutput.write("#define NBR_NODES 	      NBR_CENTRES_FORMATION + NBR_INTERFACES + NBR_APPRENANTS\n");
            textFileOutput.write("                  \n");
            textFileOutput.write("/* code des compétence en langage des signes et en codage LPC */\n");
            textFileOutput.write("#define COMPETENCE_SIGNES     0\n");
            textFileOutput.write("#define COMPETENCE_CODAGE     1\n");
            textFileOutput.write("                  \n");
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    ///* competences des interfaces en SIGNES et CODAGE*/
    //int competences_interfaces[NBR_INTERFACES][2]={
    //    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    //    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    //    {0,1},
    //    {1,0},
    //    {0,1},
    //    {1,0},
    //    {1,0},
    //    {1,0},
    //    {0,1},
    //    {1,0}
    //};
    private void writeCompetencesInterfaces() {
        try {
            textFileOutput.write("/* competences des interfaces en SIGNES et CODAGE*/\n");
            textFileOutput.write("int competences_interfaces[NBR_INTERFACES][2]={\n");
            textFileOutput.write("    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */\n");
            textFileOutput.write("    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */\n");
            int maxi = NBR_INTERFACES - 2;
            for (int i = 0; i < maxi; i++) {
		double f = rand.nextDouble() ;
                if (f < 0.1) {
                    textFileOutput.write("    {1,1}");
                } else if (f < 0.55) {
                    textFileOutput.write("    {1,0}");
                } else {
                    textFileOutput.write("    {0,1}");
                }
                if (i < maxi - 1) {
                    textFileOutput.write(",\n");
                } else {
                    textFileOutput.write("\n};\n");
                }
            }
            textFileOutput.write("                  \n");
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }

    }

    ///* spécialités des interfaces */
    //#define SPECIALITE_SANS       -1
    //#define SPECIALITE_MENUISERIE  0
    //#define SPECIALITE_ELECTRICITE 1
    //#define SPECIALITE_MECANIQUE   2
    //
    ///* specialite des interfaces */
    //int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    //    {1,0,0},
    //    {0,1,0},
    //    {0,0,0},
    //    {0,0,1},
    //    {0,1,0},
    //    {0,0,0},
    //    {0,1,0},
    //    {1,0,0},
    //    {1,0,0},
    //    {0,1,0}
    //};
    private void writeSpecialiteInterfaces() {
        try {
            textFileOutput.write("/* spécialités des interfaces */\n");
            textFileOutput.write("#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */\n");
            for (int i=0;i<NOMS_SPECIALITES.length;i++) {
                textFileOutput.write("#define "+NOMS_SPECIALITES[i]+" "+i+"\n");
            }
            textFileOutput.write("                  \n");

            textFileOutput.write("/* specialite des interfaces */\n");
            textFileOutput.write("int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={\n");

            int maxi = NBR_INTERFACES;
            for (int i = 0; i < maxi; i++) {
                int maxj = NBR_SPECIALITES;
                textFileOutput.write("    {");
                for (int j = 0; j < maxj; j++) {
                    if (rand.nextDouble() < 0.2) {
                        textFileOutput.write("1");
                    } else {
                        textFileOutput.write("0");
                    }
                    if (j < maxj - 1) {
                        textFileOutput.write(",");
                    } else {
                        textFileOutput.write("}");
                    }
                }
                if (i < maxi - 1) {
                    textFileOutput.write(",\n");
                } else {
                    textFileOutput.write("\n};\n");
                }

            }
            textFileOutput.write("                  \n");

        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    ///* coordonnées du centre, des interfaces et des apprenants */
    //float coord[NBR_NODES][2]=
    //{
    //    {565.0,575.0}, /* centre formation menuiserie */
    //    {25.0,185.0},  /* centre formation electricite */
    //    {345.0,750.0}, /* centre formation mecanique */
    //    {945.0,685.0}, /* point de départ interfaces */
    //    {845.0,655.0},
    //    {880.0,660.0},
    //    {25.0,230.0},
    //    {525.0,1000.0},
    //    {580.0,1175.0},
    //    {650.0,1130.0},
    //    {1605.0,620.0},
    //    {1220.0,580.0},
    //    {1465.0,200.0},
    //    {1530.0,5.0}, /* point de départ apprenants */
    //    {845.0,680.0},
    //    {725.0,370.0},
    //    {145.0,665.0},
    //    {415.0,635.0},
    //    {510.0,875.0},
    //    {560.0,365.0},
    //    {300.0,465.0}
    //} ;
    private void writeCoord() {
        try {
            textFileOutput.write("/* coordonnées des centres de formation, des interfaces et des apprenants */\n");
            textFileOutput.write("float coord[NBR_NODES][2]={\n");

            textFileOutput.write("                  \n");
            textFileOutput.write("    /* Les interfaces se rendent du centre SESSAD à l'école de formation */\n");

	    int maxi ;

            // Coord du centre
            maxi = 1;
            for (int i = 0; i < maxi; i++) {
                int x = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                int y = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                textFileOutput.write("    {" + x + "," + y + "}, /* centre " + i + " */\n");
            }

            textFileOutput.write("                  \n");
            textFileOutput.write("    /* Centres de formation */\n");

            // Coord des centres de formation
            maxi = NBR_SPECIALITES;
            for (int i = 0; i < maxi; i++) {
                int x = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                int y = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                textFileOutput.write("    {" + x + "," + y + "}, /* ecole formation " + NOMS_SPECIALITES[i] + " */\n");
            }

            textFileOutput.write("                  \n");
            textFileOutput.write("    /* Apprenants */\n");

            // Coord des apprenants
            maxi = NBR_APPRENANTS;
            for (int i = 0; i < maxi; i++) {
                int x = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                int y = (int) (rand.nextDouble() * DIMENSION_ZONE_GEOGRAPHIQUE);
                textFileOutput.write("    {" + x + "," + y + "}");
                if (i < maxi - 1) {
                    textFileOutput.write(", /* apprenant " + i + " */\n");
                } else {
                    textFileOutput.write("/* apprenant " + i + " */\n};\n");
                }

            }

            textFileOutput.write("                  \n");
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    //#define NBR_FORMATION          9
    //
    //#define LUNDI                  1
    //#define MARDI                  2
    //#define MERCREDI               3
    //#define JEUDI                  4
    //#define VENDREDI               5
    //#define SAMEDI                 6
    //
    ///* formation : apprenant, specialite, competence, horaire debut formation, horaire fin formation */
    //int formation[NBR_FORMATION][6]=
    //{
    //    {0,SPECIALITE_ELECTRICITE, COMPETENCE_SIGNES, LUNDI, 13, 16},
    //    {1,SPECIALITE_MENUISERIE, COMPETENCE_CODAGE, MARDI, 8, 11},
    //    {2,SPECIALITE_ELECTRICITE, COMPETENCE_CODAGE, MERCREDI, 9, 12},
    //    {3,SPECIALITE_MECANIQUE, COMPETENCE_SIGNES, MARDI, 14, 17},
    //    {4,SPECIALITE_ELECTRICITE, COMPETENCE_SIGNES, LUNDI, 9, 12},
    //    {5,SPECIALITE_MENUISERIE, COMPETENCE_SIGNES, JEUDI, 8, 11},
    //    {0,SPECIALITE_ELECTRICITE, COMPETENCE_SIGNES, JEUDI, 8, 12},
    //    {6,SPECIALITE_SANS, COMPETENCE_CODAGE, JEUDI, 14, 17},
    //    {7,SPECIALITE_ELECTRICITE, COMPETENCE_CODAGE, VENDREDI, 8, 11}
    //} ;
    private void writeFormation() {
        try {
            textFileOutput.write("#define NBR_FORMATIONS          " + NBR_FORMATIONS + "\n");
            textFileOutput.write("                  \n");
            textFileOutput.write("#define LUNDI                  1\n");
            textFileOutput.write("#define MARDI                  2\n");
            textFileOutput.write("#define MERCREDI               3\n");
            textFileOutput.write("#define JEUDI                  4\n");
            textFileOutput.write("#define VENDREDI               5\n");
            textFileOutput.write("#define SAMEDI                 6\n");
            textFileOutput.write("                  \n");

            textFileOutput.write("/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */\n");

            textFileOutput.write("int formation[NBR_FORMATIONS][6]={\n");

            int maxi = NBR_APPRENANTS;
            // public static int NBR_FORMATIONS = NBR_APPRENANTS * NBR_FORMATIONS_PAR_SEMAINE;
            for (int i = 0; i < maxi; i++) { // Apprenant i
                // {0,SPECIALITE_ELECTRICITE, COMPETENCE_SIGNES, LUNDI, 13, 16},
                int maxj = NBR_FORMATIONS_PAR_SEMAINE ;
                for (int j = 0; j < maxj; j++) { // Apprenant i
                    int spe = rand.nextInt(NBR_SPECIALITES);
                    String specialite = NOMS_SPECIALITES[spe];
                    String competence = NOMS_COMPETENCES[rand.nextInt(NBR_COMPETENCES)];
                    String jour = JOURS_SEMAINE[rand.nextInt(6)];
                    int matin = rand.nextInt(2);
                    int hdebut, hfin;
                    if (matin == 1) {
                        hdebut = 8 + rand.nextInt(3);
                        hfin = hdebut + rand.nextInt(11 - hdebut) + 2;
                    } else {
                        hdebut = 13 + rand.nextInt(4);
                        hfin = hdebut + rand.nextInt(18 - hdebut) + 2;

                    }
                    textFileOutput.write("   {" + i + "," + specialite + "," + competence + "," + jour + "," + hdebut + "," + hfin + "}");
                    if (i < maxi - 1 || j < maxj - 1) {
                        textFileOutput.write(",\n");
                    } else {
                        textFileOutput.write("\n};\n");
                    }
                }
            }

            textFileOutput.write("                  \n");
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void writeMain() {
        try {
            textFileOutput.write("// EOF\n");
        } catch (IOException ex) {
            Logger.getLogger(InstanceGenerator.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    /**
     *
     * @param string
     */
    private void log(String string) {
        System.out.println(string);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        InstanceGenerator instanceGenerator = new InstanceGenerator();

    }
}
