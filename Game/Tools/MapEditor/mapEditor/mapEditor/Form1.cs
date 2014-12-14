using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace mapEditor
{
    public partial class Form1 : Form
    {
        //Variables
        private string assetPath_Graphics;
        private Dictionary<int,tileset> tilesetList;
        private int tileSelected;
        private Graphics tilePreview;
        private Graphics mapPreview;
        private Point tilePointSelected;

        public Form1() {
            InitializeComponent();
            assetPath_Graphics = "";
            tilesetList = new Dictionary<int, tileset>();
            tileSelected = -1;
        }

        private void saveSettings() {
            System.IO.FileStream FS = new FileStream("settings.dat", FileMode.Create); //Open settings.dat file
            System.IO.BinaryWriter BW = new BinaryWriter(FS); //Create stream
            BW.Write(assetPath_Graphics); //Write the graphics asset path

            BW.Close(); //Close binary writer
            FS.Close(); //Close file stream
        }
        private void loadSettings() {
            System.IO.FileInfo FI = new FileInfo("settings.dat");
            if (FI.Exists) {
                System.IO.FileStream FS = new FileStream("settings.dat", FileMode.Open); //Open settings.dat file
                System.IO.BinaryReader BR = new BinaryReader(FS); //Create stream
                assetPath_Graphics = BR.ReadString();
                BR.Close(); //Close binary writer
                FS.Close(); //Close file stream
            }
        }

        public void loadTiles() {
            if (assetPath_Graphics == "" && Directory.Exists(assetPath_Graphics))
            {
                MessageBox.Show("Please specify a path for graphics assets path");
                assetFolderBrowser.ShowDialog();
                assetPath_Graphics = assetFolderBrowser.SelectedPath;
            }
            DirectoryInfo di = new DirectoryInfo(assetPath_Graphics+"\\tileset\\");
            FileInfo[] rgFiles = di.GetFiles("*.tile");
            foreach (FileInfo fi in rgFiles) {
                int tileID = Convert.ToInt32(fi.Name.Replace(".tile",""));
                string imagePath = assetPath_Graphics + "\\tileset\\" + tileID + ".png";
                tileset newTileset = new mapEditor.tileset();
                newTileset.imageData = new Bitmap(imagePath); //Load the tileset Image

                System.IO.FileStream FS = new FileStream(assetPath_Graphics + "\\tileset\\" + tileID + ".tile", FileMode.Open); //Open settings.dat file
                System.IO.BinaryReader BR = new BinaryReader(FS); //Create stream
                newTileset.tileWidth = BR.ReadInt16(); //Read tile width
                newTileset.tileHeight =  BR.ReadInt16(); //Read tile width
                BR.Close();
                FS.Close();

                tilesetList.Add(tileID,newTileset);

                this.cmbTileSelection.Items.Add(fi.Name);
            }


           
        }

        public void setMapSize(int width, int height)
        {
            pnlMapPreview.Image = new Bitmap(width, height);
            mapPreview = Graphics.FromImage(pnlMapPreview.Image);
            renderMapPreview();
        }

        public void initializeLayers() {
            this.cmbLayerSelection.Items.Add(1);
            this.cmbLayerSelection.SelectedIndex = 0;
        }

        private void Form1_Load(object sender, EventArgs e) {
            loadSettings(); //Load settings
            loadTiles(); //Load tile list
            initializeLayers(); //Initialize layers
            txtMapWidth.Text = "800";
            txtMapHeight.Text = "600";
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            saveSettings();
        }

        private void cmbTileSelection_SelectedIndexChanged(object sender, EventArgs e) {
            tileSelected = Convert.ToInt32(((string)cmbTileSelection.SelectedItem).Replace(".tile",""));


            //this.pnlTilePreview.Image = new Bitmap(this.tilesetList[tileSelected].imageData);
            tilePreview = pnlTilePreview.CreateGraphics();
            tilePreview.Clear(Color.Gray);
            tilePreview.DrawImage(this.tilesetList[tileSelected].imageData, 0, 0, this.tilesetList[tileSelected].imageData.Width, this.tilesetList[tileSelected].imageData.Height);

        }

        private void pnlTilePreview_Click(object sender, EventArgs e)
        {
            
        }

        private void pnlTilePreview_MouseDown(object sender, MouseEventArgs e)
        {
            if (tileSelected != -1)
            {

               decimal x = Math.Floor((decimal)e.X / 64) * 64;
               decimal y = Math.Floor((decimal)e.Y / 64) * 64;

                tilePreview.Clear(Color.Gray);
                tilePreview.DrawImage(this.tilesetList[tileSelected].imageData, 0, 0, this.tilesetList[tileSelected].imageData.Width, this.tilesetList[tileSelected].imageData.Height);
                tilePreview.DrawRectangle(new Pen(Color.Black, 2), (int)x, (int)y, this.tilesetList[tileSelected].tileWidth, this.tilesetList[tileSelected].tileHeight);
            }
        }

        private void renderMapPreview()
        {
            mapPreview.Clear(Color.DarkGray);
        }

        private void txtMapWidth_TextChanged(object sender, EventArgs e)
        {
            setMapSize(Convert.ToInt32(txtMapWidth.Text), Convert.ToInt32(txtMapHeight.Text));
        }

        private void txtMapHeight_TextChanged(object sender, EventArgs e)
        {
            setMapSize(Convert.ToInt32(txtMapWidth.Text), Convert.ToInt32(txtMapHeight.Text));
        }

        private void pnlMapPreview_MouseHover(object sender, EventArgs e)
        {
            
        }

        private void pnlMapPreview_MouseDown(object sender, MouseEventArgs e)
        {

        }

    }
}
