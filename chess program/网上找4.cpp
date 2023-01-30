//using System;
//using System.Drawing;
//using System.Net.Sockets;
//using System.IO;
//using System.Threading;
//using System.Windows.Forms;
//using System.Net;

namespace chess
{
    /*
1王 2士 3相 4马 5车 6炮 7兵
>0hei
*/

    //public partial class Form1 : Form
    {

        private Socket s;                                    //定义Socket对象
        private Thread th;                                   //客户端连接服务器的线程
        public Socket cSocket;                              //单个客户端连接的Socket对象
        private delegate void SetTextCallback();
        StreamReader sr;
        
        Move blankmove = new Move
        {
            from = new ChessPoint
            {
                x = -1,
                y = -1
            },
            to = new ChessPoint
            {
                x = -1,
                y = -1
            }
        };
       
        Bitmap bmp = new Bitmap(600, 600);


        Move bestmove;
        bool redturn = true;
        int maxdepth = 3;
        Move[,] movelist = new Move[4, 500];
        int movecount;
        int[,] map = new int[9, 10];
        int[,] tmpmap = new int[9, 10];
        ChessPoint[] relatedposition = new ChessPoint[20];
        int relatedpositioncount;
        int[] basicvalue = new int[] { 0, 10000, 250, 250, 700, 1400, 700, 100 };
        int[] basicflexibilityvalue = new int[] { 0, 0, 1, 1, 12, 6, 6, 15 };
        int[,] blacksolderbonus = new int[9, 10]
        {
            { 0,0,0,0,0,100,100,120,120,0},
            { 0,0,0,0,0,100,120,120,120,0},
            { 0,0,0,0,0,100,140,140,140,0},
            { 0,0,0,0,0,100,140,150,150,0},
            { 0,0,0,0,0,100,140,150,150,0},
            { 0,0,0,0,0,100,140,150,150,0},
            { 0,0,0,0,0,100,140,140,140,0},
            { 0,0,0,0,0,100,120,120,120,0},
            { 0,0,0,0,0,100,100,120,120,0},
        };
        int[,] redsolderbonus = new int[9, 10]
        {
            { 0,100,100,120,120,0,0,0,0,0},
            { 0,100,120,120,120,0,0,0,0,0},
            { 0,100,140,140,140,0,0,0,0,0},
            { 0,100,140,150,150,0,0,0,0,0},
            { 0,100,140,150,150,0,0,0,0,0},
            { 0,100,140,150,150,0,0,0,0,0},
            { 0,100,140,140,140,0,0,0,0,0},
            { 0,100,120,120,120,0,0,0,0,0},
            { 0,100,100,120,120,0,0,0,0,0}
        };
        int historycount = 0;
        ChessRecord[,] history = new ChessRecord[200, 4];
        ChessPoint select = new ChessPoint { x = -1, y = -1 };


        void RecoverHistory(ChessRecord h)
        {
            map[h.point.x, h.point.y] = h.what;
            RefreshChess(h.point);
        }
        struct ChessRecord
        {
            public ChessPoint point;
            public int what;
        }
        struct ChessPoint
        {
            public int x;
            public int y;
        }
        struct Move
        {
            public ChessPoint from;
            public ChessPoint to;
        }

        public void Communication()
        {
            while (true)
            {
                try
                {
                    NetworkStream ns = null;
                    if (mode == 1)
                        ns = new NetworkStream(cSocket);  //建立网络流，便于数据的读取
                    if (mode == 2)
                        ns = new NetworkStream(s);
                    sr = new StreamReader(ns);         //实例化流读取对象
                    MessageBox.Show(sr.ReadLine());
                }
                catch (SocketException ex)
                {
                    MessageBox.Show(ex.Message);           //捕获Socket异常
                }
                catch (Exception es)
                {
                    MessageBox.Show("其他异常" + es.Message);      //捕获其他异常
                }
            }
        }
        public static string ip;
        public static int mode;
        

        private string GetString(int i)
        {
            if (i == 0) return "";
            String[] str = { "帅", "仕", "相", "马", "车", "炮", "兵", "将", "士", "象", "馬", "車", "砲", "卒" };
            return str[i > 0 ? i + 6 : -i - 1];
        }

        Graphics g,gb;
        Color BoardColor = SystemColors.Control;

        public Form1()
        {
            InitializeComponent();
            gb = CreateGraphics();
            g = Graphics.FromImage(bmp);
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            InitializeChessmap();
        }
        private void InitializeChessmap()
        {
            bestmove.from.x = -1;
            bestmove.from.y = -1;
            bestmove.to.x = -1;
            bestmove.to.y = -1;

            for (int i = 0; i < 9; i++)
            {
                map[i, 0] = Math.Abs(i - 4) + 1;
            }

            for (int i = 0; i < 9; i += 2)
            {
                map[i, 3] = 7;
                map[i, 6] = -7;
            }

            for (int i = 0; i < 9; i++)
            {
                map[i, 9] = -map[i, 0];
            }
            map[1, 2] = 6;
            map[7, 2] = 6;
            map[1, 7] = -6;
            map[7, 7] = -6;

            DrawChessBoard();
        }

        int ToProcessMove(Move move)
        {
            int tochess = tmpmap[move.to.x, move.to.y];
            tmpmap[move.to.x, move.to.y] = tmpmap[move.from.x, move.from.y];
            tmpmap[move.from.x, move.from.y] = 0;
            return (tochess);
        }
        void ToRecoverMove(Move move, int tmpchess)
        {
            tmpmap[move.from.x, move.from.y] = tmpmap[move.to.x, move.to.y];
            tmpmap[move.to.x, move.to.y] = tmpchess;
        }
        int Evaluate(bool whomoves, int[,] currentmap)
        {
            int[,] flexibility = new int[9, 10];
            int[,] threatened = new int[9, 10];
            int[,] protect = new int[9, 10];
            int[,] value = new int[9, 10];
            int x, y, tmp;
            int tp, bv = 0, rv = 0, chess;
            for (y = 0; y < 10; y++)
            {
                for (x = 0; x < 9; x++)
                {
                    chess = currentmap[x, y];
                    if (chess != 0)
                    {
                        AllRelatedPosition(x, y, currentmap, false);
                        for (tmp = 0; tmp < relatedpositioncount; tmp++)
                        {
                            if (currentmap[relatedposition[tmp].x, relatedposition[tmp].y] == 0)
                            {
                                flexibility[x, y]++;
                            }
                            else if (SameColor(chess, currentmap[relatedposition[tmp].x, relatedposition[tmp].y]))
                            {
                                protect[relatedposition[tmp].x, relatedposition[tmp].y]++;
                            }
                            else
                            {
                                threatened[relatedposition[tmp].x, relatedposition[tmp].y]++;
                                flexibility[x, y]++;
                                if (currentmap[relatedposition[tmp].x, relatedposition[tmp].y] == 1)
                                {
                                    if (whomoves)
                                        return (18888);
                                }
                                else if (currentmap[relatedposition[tmp].x, relatedposition[tmp].y] == -1)
                                {
                                    if (!whomoves)
                                        return (18888);
                                }
                                else
                                {
                                    threatened[relatedposition[tmp].x, relatedposition[tmp].y] += (30 + (basicvalue[Math.Abs(currentmap[relatedposition[tmp].x, relatedposition[tmp].y])] - basicvalue[Math.Abs(chess)]) / 10) / 10;
                                }
                            }
                        }
                    }
                }
            }
            for (y = 0; y < 10; y++)
            {
                for (x = 0; x < 9; x++)
                {
                    chess = currentmap[x, y];
                    if (chess != 0)
                    {
                        value[x, y]++;
                        value[x, y] += basicflexibilityvalue[Math.Abs(chess)] * flexibility[x, y];
                        if (chess == 7)
                        {
                            value[x, y] = basicvalue[Math.Abs(chess)] + blacksolderbonus[x, y];
                        }
                        else if (chess == -7)
                        {
                            value[x, y] = basicvalue[Math.Abs(chess)] + redsolderbonus[x, y];
                        }
                    }
                    //Console.Write(value[x, y]);
                    //Console.Write(" ");
                }
                //Console.Write("\n");
            }
            for (y = 0; y < 10; y++)
            {
                for (x = 0; x < 9; x++)
                {
                    chess = currentmap[x, y];
                    if (chess != 0)
                    {
                        tp = basicvalue[Math.Abs(chess)] / 16;
                        value[x, y] += basicvalue[Math.Abs(chess)];
                        if (threatened[x, y] != 0)
                        {
                            if (whomoves == (chess < 0 ? true : false))
                            {
                                if (chess == (chess < 0 ? -1 : 1))
                                {
                                    value[x, y] -= 20;
                                }
                                else
                                {
                                    value[x, y] -= 2 * tp;
                                    if (protect[x, y] != 0)
                                    {
                                        value[x, y] += tp;
                                    }
                                }
                            }
                            else
                            {
                                if (chess == (chess < 0 ? -1 : 1))
                                    return (18888);
                                value[x, y] -= 10 * tp;
                                if (protect[x, y] != 0)
                                {
                                    value[x, y] += 9 * tp;
                                }
                            }
                            value[x, y] -= threatened[x, y];
                        }
                        else
                        {
                            if (protect[x, y] != 0)
                            {
                                value[x, y] += 5;
                            }
                        }

                    }
                    //Console.Write(value[x, y]);
                    //Console.Write(" ");
                }
                //Console.Write("\n");
            }
            for (y = 0; y < 10; y++)
            {
                for (x = 0; x < 9; x++)
                {
                    chess = currentmap[x, y];
                    if (chess != 0)
                    {
                        if (chess > 0) bv += value[x, y];
                        else rv += value[x, y];
                    }
                }
            }
            if (whomoves) retur
n (rv - bv);
            else return (bv - rv);
        }
        int ABSearch(int up, int down, int depth)
        {
            int score, count, v1;
            bool thatside;
            int tmpchess;
            if ((maxdepth - depth) % 2 == 1) thatside = !redturn;
            else thatside = redturn;
            v1 = GameEnd(depth, tmpmap);
            if (v1 != 0) return v1;
            if (depth <= 0) return (Evaluate(thatside, tmpmap));
            count = GenerateMove(depth, thatside, tmpmap);
            //Console.WriteLine(count);
            for (v1 = 0; v1 < count; v1++)
            {
                tmpchess = ToProcessMove(movelist[depth, v1]);
                //Console.WriteLine(movelist[depth, v1].from.x.ToString() + "," + movelist[depth, v1].from.y.ToString() + "->" + movelist[depth, v1].to.x.ToString() + "," + movelist[depth, v1].to.y.ToString() );
                score = -ABSearch(-down, -up, depth - 1);
                //Console.WriteLine(score);
                ToRecoverMove(movelist[depth, v1], tmpchess);
                if (score > up)
                {
                    up = score;
                    if (depth == maxdepth)
                    {
                        bestmove = movelist[depth, v1];
                    }
                }
                if (up >= down) break;
            }
            return up;
        }

        int GenerateMove(int level, bool thatside, int[,] currentmap)
        {
            movecount = 0;
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (!thatside && currentmap[i, j] > 0 || thatside && currentmap[i, j] < 0)
                    {
                        AllRelatedPosition(i, j, currentmap, true, level);
                    }
                }
            }
            return movecount;
        }

        bool SameColor(int v1, int v2)
        {
            return (v1 > 0 && v2 > 0 || v1 < 0 && v2 < 0);
        }
        int AllRelatedPosition(int x, int y, int[,] currentmap, bool gothere, int level = -1)
        {
            int v1, v2;//x,y
            ChessPoint from, to;
            relatedpositioncount = 0;
            from.x = x;
            from.y = y;
            if (Math.Abs(currentmap[from.x, from.y]) == 1)
            {
                for (v2 = 0; v2 <= 2; v2++)
                {
                    for (v1 = 3; v1 <= 5; v1++)
                    {
                        to.x = v1;
                        to.y = v2;
                        if (WhetherAccessible(from, to, currentmap, gothere))
                        {
                            InsertRelatedPosition(from, to, level);
                        }
                    }
                }
                for (v2 = 7; v2 <= 9; v2++)
                {
                    for (v1 = 3; v1 <= 5; v1++)
                    {
                        to.x = v1;
                        to.y = v2;
                        if (WhetherAccessible(from, to, currentmap, gothere))
                        {
                            InsertRelatedPosition(from, to, level);
                        }
                    }
                }
            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 5 || Math.Abs(currentmap[from.x, from.y]) == 6)
            {
                for (int i = 0; i < 9; i++)
                {
                    to.x = i;
                    to.y = from.y;
                    if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                }
                for (int i = 0; i < 10; i++)
                {
                    to.x = from.x;
                    to.y = i;
                    if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                }
            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 2)
            {
                for (int i = -1; i <= 1; i += 2)
                {
                    for (int j = -1; j <= 1; j += 2)
                    {
                        to.x = from.x + i;
                        to.y = from.y + j;
                        if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                    }
                }
            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 3)
            {
                for (int i = -2; i <= 2; i += 4)
                {
                    for (int j = -2; j <= 2; j += 4)
                    {
                        to.x = from.x + i;
                        to.y = from.y + j;
                        if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                    }
                }
            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 7)
            {
                to.x = from.x; to.y = from.y + 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x; to.y = from.y - 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x + 1; to.y = from.y;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x - 1; to.y = from.y;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);

            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 4)
            {
                to.x = from.x + 2; to.y = from.y + 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x + 2; to.y = from.y - 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x + 1; to.y = from.y + 2;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x + 1; to.y = from.y - 2;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x - 2; to.y = from.y + 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x - 2; to.y = from.y - 1;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x - 1; to.y = from.y + 2;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);
                to.x = from.x - 1; to.y = from.y - 2;
                if (WhetherAccessible(from, to, currentmap, gothere)) InsertRelatedPosition(from, to, level);

            }
            return relatedpositioncount;
        }
        int GameEnd(int depth, int[,] currentmap)
        {
            bool redalive = false, blackalive = false;
            int x, y, tmp;
            for (y = 0; y <= 2; y++)
            {
                for (x = 3; x <= 5; x++)
                {
                    if (currentmap[x, y] == 1) blackalive = true;
                    if (currentmap[x, y] == -1) redalive = true;
                }
            }
            for (y = 7; y <= 9; y++)
            {
                for (x = 3; x <= 5; x++)
                {
                    if (currentmap[x, y] == 1) blackalive = true;
                    if (currentmap[x, y] == -1) redalive = true;
                }
            }
            tmp = (maxdepth - depth + 1) % 2;
            if (!redalive)
            {
                if (tmp == 1) return 19999 + depth;
                return -19999 - depth;
            }
            if (!blackalive)
            {
                if (tmp == 1) return -19999 - depth;
                return +19999 + depth;
            }
            return 0;
        }
        void InsertRelatedPosition(ChessPoint from, ChessPoint position, int level)
        {
            //Console.WriteLine("added related position:from" + from.x.ToString() + "," + from.y.ToString() + "->" + position.x.ToString() + "," + position.y.ToString());
            if (level == -1)
            {
                relatedposition[relatedpositioncount] = position;
                relatedpositioncount++;
            }
            else
            {
                movelist[level, movecount].from = from;
                movelist[level, movecount].to = position;
                movecount++;
            }
        }
        bool WhetherAccessible(ChessPoint from, ChessPoint to, int[,] currentmap, bool gothere)
        {
            int fromchess, tochess;
            fromchess = currentmap[from.x, from.y];
            if (to.x < 0 || to.x > 8 || to.y < 0 || to.y > 9) return false;
            tochess = currentmap[to.x, to.y];
            if (from.Equals(to)) return false;
            if (gothere && SameColor(fromchess, tochess)) return false;
            if (Math.Abs(fromchess) == 1)
            {
                if (to.y > 2 && to.y < 7 || to.x > 5 || to.x < 3) return false;
                if (Math.Abs(from.x - to.x) + Math.Abs(from.y - to.y) > 1) return false;
                if (tochess == -fromchess)
                {
                    for (int i = to.y + (from.y > to.y ? 1 : -1); i != from.y; i += (from.y > to.y ? 1 : -1))
                    {
                        if (currentmap[to.x, i] != 0) return false;
                    }
                }
            }

            else if (fromchess == -2)
            {
                if (to.y < 7 || to.x < 3 || to.x > 5) return false;
                if (Math.Abs(from.x - to.x) != 1 || Math.Abs(from.y - to.y) != 1) return false;
            }
            else if (fromchess == 2)
            {
                if (to.y > 2 || to.x < 3 || to.x > 5) return false;
                if (Math.Abs(from.x - to.x) != 1 || Math.Abs(from.y - to.y) != 1) return false;
            }
            else if (fromchess == -3)
            {
                if (to.y < 5) return false;
                if (Math.Abs(from.x - to.x) != 2 || Math.Abs(from.y - to.y) != 2) return false;
                if (currentmap[(from.x + to.x) / 2, (from.y + to.y) / 2] != 0) return false;
            }
            else if (fromchess == 3)
            {
                if (to.y > 4) return false;
                if (Math.Abs(from.x - to.x) != 2 || Math.Abs(from.y - to.y) != 2) return false;
                if (currentmap[(from.x + to.x) / 2, (from.y + to.y) / 2] != 0) return false;
            }
            else if (fromchess == 7)
            {
                if (to.y < from.y) return false;
                if (from.y < 5 && from.y == to.y) return false;
                if (from.y - to.y + Math.Abs(from.x - to.x) > 1) return false;
            }
            else if (fromchess == -7)
            {
                if (to.y > from.y) return false;
                if (from.y > 4 && from.y == to.y) return false;
                if (from.y - to.y + Math.Abs(from.x - to.x) > 1) return false;
            }
            else if (Math.Abs(fromchess) == 4)
            {
                if (Math.Abs(to.x - from.x) + Math.Abs(to.y - from.y) != 3) return false;
                if (to.x == from.x || to.y == from.y) return false;
                if (Math.Abs(to.x - from.x) == 2)
                {
                    if (currentmap[(to.x + from.x) / 2, from.y] != 0) return false;
                }
                else if (currentmap[from.x, (to.y + from.y) / 2] != 0) return false;
            }
            else if (Math.Abs(fromchess) == 5)
            {
                if (from.x == to.x)
                {
                    for (int i = to.y + (from.y > to.y ? 1 : -1); i != from.y; i += (from.y > to.y ? 1 : -1))
                    {
                        if (currentmap[to.x, i] != 0) return false;
                    }
                }
                else if (from.y == to.y)
                {
                    for (int i = to.x + (from.x > to.x ? 1 : -1); i != from.x; i += (from.x > to.x ? 1 : -1))
                    {
                        if (currentmap[i, to.y] != 0) return false;
                    }
                }
                else return false;
            }
            else if (Math.Abs(currentmap[from.x, from.y]) == 6)
            {
                int j = 0;
                if (to.x == from.x)
                {
                    for (int i = to.y + (from.y > to.y ? 1 : -1); i != from.y; i += (from.y > to.y ? 1 : -1))
                    {
                        if (currentmap[to.x, i] != 0) j++;
                    }
                    if (j > 1 || j == 1 && currentmap[to.x, to.y] == 0 || j == 0 && currentmap[to.x, to.y] != 0) return false;
                }
                else if (to.y == from.y)
                {
                    for (int i = to.x + (from.x > to.x ? 1 : -1); i != from.x; i += (from.x > to.x ? 1 : -1))
                    {
                        if (currentmap[i, to.y] != 0) j++;
                    }
                    if (j > 1 || j == 1 && currentmap[to.x, to.y] == 0 || j == 0 && currentmap[to.x, to.y] != 0) return false;
                }
                else return false;
            }
            return true;
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            //Form2 f = new Form2();
            //f.Show(this);
        }
        private void RefreshChess(ChessPoint where)
        {
            int x = where.x, y = where.y;
            if (x < 0 || y < 0) return;
            bool selected = false;
            if (x == select.x && y == select.y)
            {
                selected = true;
            }
            g.FillRectangle(new SolidBrush(BoardColor), x * 40 + 20, y * 40 + 20, 40, 40);
            g.DrawLine(Pens.Black, x * 40 + 40 + (x == 0 ? 0 : -20), y * 40 + 40, x * 40 + 40 + (x == 8 ? 0 : 20), y * 40 + 40);
            g.DrawLine(Pens.Black, x * 40 + 40, y * 40 + 40 + (y == 0 || y == 5 ? 0 : -20), x * 40 + 40, y * 40 + 40 + (y == 4 || y == 9 ? 0 : 20));
            if (x >= 3 && x <= 5 && (y >= 0 && y <= 2 || y >= 7 && y <= 9))
            {
                if (x == 4 && (y == 1 || y == 8))
                {
                    g.DrawLine(Pens.Black, x * 40 + 20, y * 40 + 20, x * 40 + 60, y * 40 + 60);
                    g.DrawLine(Pens.Black, x * 40 + 20, y * 40 + 60, x * 40 + 60, y * 40 + 20);
                }
                else
                {
                    if (y != 1 && y != 8 && x != 4)
                        g.DrawLine(Pens.Black, x * 40 + 40, y * 40 + 40, x * 40 + 40 + (x == 3 ? +20 : -20), y * 40 + 40 + (y == 0 || y == 7 ? +20 : -20));
                }

            }
            string str = GetString(map[x, y]);
            if (str != "")
                g.FillEllipse(new SolidBrush(selected ? Color.BlueViolet : map[x, y] > 0 ? Color.Black : Color.Red), x * 40 + 40 - 15, y * 40 + 40 - 15, 30, 30);
            if (x == bestmove.from.x && y == bestmove.from.y || x == bestmove.to.x && y == bestmove.to.y)
            {
                g.DrawEllipse(new Pen(Color.Orange, 2), x * 40 + 40 - 15, y * 40 + 40 - 15, 30, 30); ;
            }
            if (str != "")
            {
                StringFormat strf = new StringFormat
                {
                    LineAlignment = StringAlignment.Center,
                    Alignment = StringAlignment.Center
                };
                g.DrawString(str, new Font("微软雅黑", 14, FontStyle.Regular), Brushes.White, x * 40 + 40, y * 40 + 40, strf);
            }
            Form1_Paint(null, null);
        }


        private void DrawChessBoard()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    RefreshChess(new ChessPoint { x = i, y = j });
                }
            }
        }

        private void Play_Click(object sender, EventArgs e)
        {

        }

        private void Debug_Click(object sender, EventArgs e)
        {

            int time = Environment.TickCount;
            Move tmpmove = bestmove;
            Text = "Thinking...";
            tmpmap = map;
            bestmove = blankmove;
            RefreshChess(tmpmove.from);
            RefreshChess(tmpmove.to);

            ABSearch(-20000, 20000, maxdepth);
            if (bestmove.from.x == -1)
            {
                MessageBox.Show("游戏结束");
                return;
            }

            history[historycount, 2].point = bestmove.from;
            history[historycount, 2].what = map[bestmove.from.x, bestmove.from.y];
            history[historycount, 3].point = bestmove.to;
            history[historycount, 3].what = map[bestmove.to.x, bestmove.to.y];
            map[bestmove.to.x, bestmove.to.y] = map[bestmove.from.x, bestmove.from.y];
            map[bestmove.from.x, bestmove.from.y] = 0;
            RefreshChess(bestmove.from);
            RefreshChess(bestmove.to);
            //Text = bestmove.from.x.ToString() + "," + bestmove.from.y.ToString() + "->" + bestmove.to.x.ToString() + "," + bestmove.to.y.ToString();
            Text = (Environment.TickCount - time).ToString() + "ms";
            historycount++;
            redturn = !redturn;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            gb.DrawImage(bmp,0,0);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button1.Enabled = false;
            s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);//创建Socket对象
            if (mode == 1)
            {
                IPAddress serverIP = IPAddress.Parse("0.0.0.0");
                IPEndPoint server = new IPEndPoint(serverIP, 7549);    //实例化服务器的IP和端口
                try
                {
                    s.Bind(server);
                }
                catch (Exception exx)
                {
                    MessageBox.Show(exx.Message);
                }
                s.Listen(10);
                cSocket = s.Accept();

            }
            if (mode == 2)
            {
                s.Connect(IPAddress.Parse("127.0.0.1"), 7549);
            }
            try
            {
                th = new Thread(new ThreadStart(Communication));     //创建线程
                th.Start();                                                //启动线程
                Text = "启动成功！";
            }
            catch (Exception ex)
            {
                MessageBox.Show("启动失败！" + ex.Message);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            redturn = false;
            Console.WriteLine(Evaluate(false, map));
            //Console.WriteLine(WhetherAccessible(new ChessPoint { x = 4, y = 9 }, new ChessPoint { x = 3, y = 9 },map,true));

            return;
            NetworkStream ns = null;
            if (mode == 1)
                ns = new NetworkStream(s);
            if (mode == 2)
                ns = new NetworkStream(cSocket);
            StreamWriter sw = new StreamWriter(ns);
            sw.Write(textBox1.Text);
            sw.Flush();
        }



        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                if (historycount == 0) return;
                select.x = -1;
                select.y = -1;
                bestmove = blankmove;
                historycount--;
                RecoverHistory(history[historycount, 3]);
                RecoverHistory(history[historycount, 2]);
                RecoverHistory(history[historycount, 1]);
                RecoverHistory(history[historycount, 0]);
                return;
            }
            bool gangganghao = false;
            ChessPoint pointpoint;
            pointpoint.x = Convert.ToInt32(Math.Round(1.0 * e.X / 40) * 40);
            pointpoint.y = Convert.ToInt32(Math.Round(1.0 * e.Y / 40) * 40);
            if ((e.X - pointpoint.x) * (e.X - pointpoint.x) + (e.Y - pointpoint.y) * (e.Y - pointpoint.y) < 225) gangganghao = true;

            pointpoint.x = pointpoint.x / 40 - 1;
            pointpoint.y = pointpoint.y / 40 - 1;
            if (pointpoint.x > 8 || pointpoint.y > 9) return;
            ChessPoint tmp = select;
            if (select.x != -1 || select.y != -1)
            {
                if (select.x == pointpoint.x && select.y == pointpoint.y) return;
                if (map[pointpoint.x, pointpoint.y] > 0 && map[select.x, select.y] > 0 || map[pointpoint.x, pointpoint.y] < 0 && map[select.x, select.y] < 0)
                {
                    select = pointpoint;
                    RefreshChess(tmp);
                    RefreshChess(pointpoint);
                    return;
                }
                if (WhetherAccessible(select, pointpoint, map, true) == false) return;
                select.x = -1;
                select.y = -1;
                history[historycount, 0].point = tmp;
                history[historycount, 0].what = map[tmp.x, tmp.y];
                history[historycount, 1].point = pointpoint;
                history[historycount, 1].what = map[pointpoint.x, pointpoint.y];
                map[pointpoint.x, pointpoint.y] = map[tmp.x, tmp.y];
                map[tmp.x, tmp.y] = 0;
                RefreshChess(pointpoint);
                RefreshChess(tmp);
                redturn = !redturn;
                Debug_Click(null, null);
            }
            else
            {
                if (gangganghao == false) return;
                if (select.x == pointpoint.x && select.y == pointpoint.y) return;
                if (map[pointpoint.x, pointpoint.y] == 0) return;
                if (map[pointpoint.x, pointpoint.y] > 0 == redturn) return;
                select = pointpoint;
                if (tmp.x != -1 || tmp.y != -1)
                    RefreshChess(tmp);
                RefreshChess(pointpoint);
            }

        }

    }

}
