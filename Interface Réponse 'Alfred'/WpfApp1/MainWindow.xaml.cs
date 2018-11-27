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
        private String IP = "10.16.3.214";
        private int port = 53000;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void valider_Click(object sender, RoutedEventArgs e)
        {
            if (champReponse.Text[champReponse.Text.Length - 1] == ' ')
            {
                champReponse.SelectionStart = 0;
                champReponse.SelectionLength = champReponse.Text.Length - 1;
                champReponse.Text = champReponse.SelectedText;
            }
            if (champReponse.Text == "réponse")
            {
                //client = new TcpClient(IP, port);
                //NetworkStream nwStream = client.GetStream();
                //byte[] bytesToSend = ASCIIEncoding.ASCII.GetBytes("GAGNE:04");

                //Console.WriteLine("Sending : GAGNE:04");
                // nwStream.Write(bytesToSend, 0, bytesToSend.Length);
                // try
                //{
                //   client.Connect(IP,port);
                //}
                // catch (Exception ex)
                //{
                //     MessageBox.Show("Error : " + ex.Message);
                // }
                Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipAdd = System.Net.IPAddress.Parse(IP);
                IPEndPoint remoteEP = new IPEndPoint(ipAdd, port);

                socket.Connect(remoteEP);

                byte[] byData = System.Text.Encoding.ASCII.GetBytes("GAGNE:4");
                socket.Send(byData);


                socket.Disconnect(false);
                socket.Close();
                MessageBox.Show("Bravo! Vous avez résolu l'enigme.", "Bravo!");
            }
            else if (champReponse.Text != "Laos")
            {
                MessageBox.Show("FAUX! Réessayez!", "Raté");
                champReponse.Text = "";
            }
        }

        private void Indices_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Insérez indice ici!\nInsérez indice ici\nInsérer indice ici", "Indices");
        }

        private void mehdi_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Il y a un correcteur d'ortographe.\nIl suffit d'appuyer sur \"ESPACE\" à la fin de votre réponse.\n\n-Mehdi （ゝ‿ ・）","Note du dev");
        }

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
