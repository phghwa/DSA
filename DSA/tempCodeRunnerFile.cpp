int n = 7, m = 11;
    int a[n+1][n+1] = {0};  // Đặt giá trị mặc định là 0 (vì không có cạnh)

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    
}