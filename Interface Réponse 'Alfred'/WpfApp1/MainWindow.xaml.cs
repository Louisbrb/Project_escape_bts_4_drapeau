using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.Net.Sockets;
using System.Text.RegularExpressions;

namespace WpfApp1
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private String reponse = "Laos"; //la bonne réponse
        private String IP = "10.16.3.214"; //l'adresse IP du serveur
        private int port = 53000; //le port d'écoute du serveur

        public MainWindow()
        {
            InitializeComponent();
        }

        //bouton valider
        private void valider_Click(object sender, RoutedEventArgs e)
        {
            if (champReponse.Text[champReponse.Text.Length - 1] == ' ')
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length - 1;
                champReponse.Text = champReponse.SelectedText;
            }

            //condition pour une bonne réponse
            if (champReponse.Text == reponse)
            {
                //envoie d'un string au serveur via socket
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipAdd = System.Net.IPAddress.Parse(IP);
                IPEndPoint remoteEP = new IPEndPoint(ipAdd, port);

                socket.Connect(remoteEP);

                byte[] byData = System.Text.Encoding.ASCII.GetBytes("GAGNE:4");
                socket.Send(byData);

                //deconnexion du socket pour le réutiliser et message de victoire
                socket.Disconnect(false);
                socket.Close();
                MessageBox.Show("Bravo! Vous avez résolu l'enigme.", "Victoire!");
            }

            //mauvaise réponse
            else if (champReponse.Text != reponse)
            {
                MessageBox.Show("FAUX! Réessayez!", "Raté");
                champReponse.Text = "";
            }
        }

        //bouton indice
        private void Indices_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Insérez indice ici!\nInsérez indice ici\nInsérer indice ici", "Indices");
        }

        //bouton message du dev
        private void mehdi_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Il y a un correcteur d'ortographe.\nIl suffit d'appuyer sur \"ESPACE\" à la fin de votre réponse.\n\n-Mehdi （ゝ‿ ・）","Note du dev");
        }

        //selection du texte lors d'un focus sur le champ de texte
        private void champReponse_GotFocus(object sender, RoutedEventArgs e)
        {
            if (champReponse.Text == "Entrez réponse")
            {
                champReponse.Text = "";
            }
            else if (champReponse.Text != "Entrez réponse")
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length;
            }
        }

        //selection du texte lors d'un clic sur le champ de texte
        private void champReponse_GotMouseCapture(object sender, MouseEventArgs e)
        {
            if (champReponse.Text == "Entrez réponse")
            {
                champReponse.Text = "";
            }
            else if (champReponse.Text != "Entrez réponse")
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length;
            }
        }
    }
}
